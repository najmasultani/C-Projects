# Seam Carving

This project implements a content-aware image resizing technique known as seam carving. Seam carving allows for the reduction of an image's size while preserving its important features, making it a powerful tool in image processing.

## Objective

The goal of this project is to create a data type that can resize an image by removing seams, which are defined paths of pixels connected either vertically or horizontally. The project involves calculating the dual-gradient energy function and identifying the minimum-energy seams to remove from the image.

## Features

- **Dual-Gradient Energy Calculation**: Computes the energy of each pixel based on the dual-gradient energy function, which helps determine the importance of pixels for seam carving.
- **Seam Identification**: Uses dynamic programming to identify vertical seams of minimal total energy.
- **Seam Removal**: Removes identified seams from the image to achieve the desired size.
- **Visual Representation**: Visualizes the energy and seam information to demonstrate the effectiveness of the seam carving technique.

## Key Functions

### `void calc_energy(struct rgb_img *im, struct rgb_img **grad)`
- **Description**: Calculates the dual-gradient energy function for the given image and stores it in `grad`.
- **Input**:
  - `im`: Pointer to the input image.
  - `grad`: Pointer to the output image for storing the energy values.

### `void dynamic_seam(struct rgb_img *grad, double **best_arr)`
- **Description**: Allocates and computes the dynamic array `best_arr` to store the minimum cost of seams.
- **Input**:
  - `grad`: Pointer to the gradient image.
  - `best_arr`: Pointer to the array for storing the minimum costs.

### `void recover_path(double *best, int height, int width, int **path)`
- **Description**: Allocates a path through the minimum seam as defined by the array `best`.
- **Input**:
  - `best`: Array containing the minimum costs.
  - `height`: Height of the image.
  - `width`: Width of the image.
  - `path`: Pointer to the output path array.

### `void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)`
- **Description**: Creates a new image by removing the seam defined in `path` from the source image `src`.
- **Input**:
  - `src`: Pointer to the source image.
  - `dest`: Pointer to the destination image.
  - `path`: Array defining the seam to be removed.
    
## Resources: 
This project was originally developed as part of the **ESC190: Data Structures and Algorithms course** assignment at the University of Toronto.

## How to Run

### Clone the repository:

```bash
git clone https://github.com/najmasultani/C-Projects-General.git

# Navigate to the Seam Carving folder
cd C-Projects-General/SeamCarving

# Compile the project
gcc -Wall -std=99 seamcarving.c main.c -o seamcarving

# Run the program
./seamcarving
