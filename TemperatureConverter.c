/*
 * Project Title: Temperature Converter
 *
 * Project Description:
 * This program converts temperatures between Fahrenheit and Celsius. It prompts the user
 * to enter a temperature value and the desired unit ('F' for Fahrenheit or 'C' for Celsius).
 * The program performs the conversion and displays the converted temperature to the user.
 * Input validation is implemented to ensure that the user enters a valid unit.
 */

#include <stdio.h>

double tempConverter(); // Function declaration

char unit;
double degree;

int main() {
    printf("Enter 'F' for Fahrenheit or 'C' for Celsius: ");
    scanf(" %c", &unit); // Added space before %c to consume any leading whitespace

    // Input validation
    while (unit != 'F' && unit != 'C') {
        printf("Invalid input. Enter 'F' for Fahrenheit or 'C' for Celsius: ");
        scanf(" %c", &unit);
    }

    printf("Enter the degree: ");
    scanf("%lf", &degree);

    double convertedTemperature = tempConverter();
    printf("Converted temperature: %.2lf%c\n", convertedTemperature, unit);

    return 0;
}

double tempConverter() {
    if (unit == 'F') {
        double celsius = (degree - 32) * 5 / 9;
        return celsius;
    } else if (unit == 'C') {
        double fahrenheit = (degree * 9 / 5) + 32;
        return fahrenheit;
    }
    // Default case, return 0 if an invalid unit is provided
    return 0;
}
