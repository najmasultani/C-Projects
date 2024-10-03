#include "seamcarving.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "c_img.h"

// Function to calculate the energy of each pixel in the image
void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
    // Create an image to store the gradient energy
    create_img(grad, im->height, im->width);
    
    // Iterate through each pixel in the image
    for (int i = 0; i < im->height; i++) {
        for (int j = 0; j < im->width; j++) {
            // Calculate neighboring pixel values for gradient calculations
            int r_l = get_pixel(im, i, (j - 1 + im->width) % im->width, 0); // Left pixel (wrap around)
            int g_l = get_pixel(im, i, (j - 1 + im->width) % im->width, 1);
            int b_l = get_pixel(im, i, (j - 1 + im->width) % im->width, 2);

            int r_r = get_pixel(im, i, (j + 1) % im->width, 0); // Right pixel
            int g_r = get_pixel(im, i, (j + 1) % im->width, 1);
            int b_r = get_pixel(im, i, (j + 1) % im->width, 2);

            // Calculate the gradient in the x-direction
            int d_rx = r_r - r_l;
            int d_gx = g_r - g_l;
            int d_bx = b_r - b_l;

            int r_up = get_pixel(im, (i - 1 + im->height) % im->height, j, 0); // Upper pixel (wrap around)
            int g_up = get_pixel(im, (i - 1 + im->height) % im->height, j, 1);
            int b_up = get_pixel(im, (i - 1 + im->height) % im->height, j, 2);

            int r_down = get_pixel(im, (i + 1) % im->height, j, 0); // Lower pixel
            int g_down = get_pixel(im, (i + 1) % im->height, j, 1);
            int b_down = get_pixel(im, (i + 1) % im->height, j, 2);

            // Calculate the gradient in the y-direction
            int d_ry = r_up - r_down;
            int d_gy = g_up - g_down;
            int d_by = b_up - b_down;

            // Compute energy values for the pixel
            int e_x = pow(d_rx, 2) + pow(d_gx, 2) + pow(d_bx, 2);
            int e_y = pow(d_ry, 2) + pow(d_gy, 2) + pow(d_by, 2);
            
            // Calculate the total energy using the dual-gradient function
            int e = sqrt(e_y + e_x);
            
            // Store the dual-gradient energy in an image, normalized to grayscale
            uint8_t total_e = (uint8_t)(e / 10);
            set_pixel(*grad, i, j, total_e, total_e, total_e); // Set RGB values to the same energy value
        }
    }
}

// Part 2: Cost Array
// This function allocates and computes the dynamic array of the minimum cost of each pixel in the image.
void dynamic_seam(struct rgb_img *grad, double **best_arr) {
    // Allocate memory for the best_arr
    *best_arr = (double *)malloc(sizeof(double) * grad->height * grad->width);

    // Initialize the first row of best_arr with gradient energy values
    for (int i = 0; i < grad->width; i++) {
        (*best_arr)[i] = get_pixel(grad, 0, i, 0); 
    }
    
    // Calculate the minimum cost for each pixel in the image
    for (int j = 1; j < grad->height; j++) {
        for (int i = 0; i < grad->width; i++) {
            // Start with the cost from the pixel directly above
            double minimum_cost = (*best_arr)[(j - 1) * grad->width + i];

            // Check the left diagonal pixel (if within bounds)
            if (i > 0) {
                minimum_cost = fmin(minimum_cost, (*best_arr)[(j - 1) * grad->width + i - 1]);
            }

            // Check the right diagonal pixel (if within bounds)
            if (i < grad->width - 1) {
                minimum_cost = fmin(minimum_cost, (*best_arr)[(j - 1) * grad->width + i + 1]);
            }

            // Store the total minimum cost for the current pixel
            (*best_arr)[j * grad->width + i] = minimum_cost + get_pixel(grad, j, i, 0);
        }
    }
}

// Part 3: Recover The Seam
// This function allocates a path through the minimum seam as defined by the array best.
void recover_path(double *best, int height, int width, int **path) {
    // Allocate memory for the path
    *path = (int *)malloc(height * sizeof(int));

    // Find the index of the minimum value in the last row
    int index = 0;
    for (int i = 1; i < width; i++) {
        if (best[(height - 1) * width + i] < best[(height - 1) * width + index]) {
            index = i; // Update index if a new minimum is found
        }
    }
    (*path)[height - 1] = index; // Set the last path value

    // Backtrack through the best array to find the entire path
    for (int i = height - 2; i >= 0; i--) {
        int cur = (*path)[i + 1];
       
        int l = (cur > 0) ? cur - 1 : cur; // Left neighbor
        int r = (cur < width - 1) ? cur + 1 : cur; // Right neighbor
        int min_neighbor = cur; 
        double min_value = best[i * width + cur]; 

        // Check if left neighbor has a lower cost
        if (l != cur && best[i * width + l] < min_value) {
            min_neighbor = l;
            min_value = best[i * width + l];
        }

        // Check if right neighbor has a lower cost
        if (r != cur && best[i * width + r] < min_value) {
            min_neighbor = r;
        }

        // Set the current path value
        (*path)[i] = min_neighbor;
    }
}

// Part 4: 
// This function creates the destination image and writes to it the source image, with the seam removed.
void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path) {
    // Create the destination image with one less column
    create_img(dest, src->height, src->width - 1);

    // Iterate through each row of the source image
    for (int row = 0; row < src->height; row++) {
        int dest_col = 0; // Initialize destination column index

        // Iterate through each column of the source image
        for (int src_col = 0; src_col < src->width; src_col++) {
            // Skip the column that is part of the seam
            if (src_col != path[row]) {
                // Get pixel values from the source image
                uint8_t r = get_pixel(src, row, src_col, 0);
                uint8_t g = get_pixel(src, row, src_col, 1);
                uint8_t b = get_pixel(src, row, src_col, 2);
                
                // Set pixel values in the destination image
                set_pixel(*dest, row, dest_col, r, g, b);
                dest_col++; // Move to the next destination column
            }
        }
    }
}

// Main function (commented out for now)
// int main() {
//     struct rgb_img *im;
//     struct rgb_img *grad;
//     double *best;
//     int *path;
//     read_in_img(&im, "HJoceanSmall.bin");
//     for(int i = 0; i < 5; i++) {
//         printf("i = %d\n", i);
//         calc_energy(im, &grad); 
//         dynamic_seam(grad, &best); 
//         recover_path(best, grad->height, grad->width, &path); 
//         struct rgb_img *cur_im;
//         remove_seam(im, &cur_im, path); 

//         char filename[200];
//         sprintf(filename, "img%d.bin", i); 
//         write_img(cur_im, filename);
//         if (i > 0) { 
//             destroy_image(im);
//         }
//         destroy_image(grad); 
//         free(best); 
//         free(path); 
//         im = cur_im; 
//     }
//     destroy_image(im); 
//     return 0;
// }
