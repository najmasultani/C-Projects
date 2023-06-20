/* Project Title: Basic Calculator
 * 
 * Description: This program is a basic calculator that performs addition, subtraction,
 * multiplication, and division operations on two numbers. It prompts the user to enter
 * the numbers and an operator, and then displays the result of the operation.
 * The program also handles the case of division by zero and provides appropriate error
 * messages.
 */

#include <stdio.h>

int main() {
    char operator;
    double num1 = 0.0;
    double num2 = 0.0;

    // Prompt the user to enter the first number
    printf("Enter a number: ");
    scanf("%lf", &num1);

    // Prompt the user to enter the second number
    printf("Enter another number: ");
    scanf("%lf", &num2);

    // Prompt the user to enter an operator
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    // Perform the selected operation and display the result
    if (operator == '+') {
        printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
    }
    else if (operator == '-') {
        printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
    }
    else if (operator == '*') {
        printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
    }
    else if (operator == '/') {
        if (num2 == 0) {
            printf("Error!\nDivision by zero!\n");
        }
        else {
            printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
        }
    }
    else {
        printf("Invalid operation entered. Please try again!\n");
    }

    return 0;
}
