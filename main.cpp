#include "poly_gpt.h"
#include "poly_copilot.h"
#include <iostream>
#include <vector>

// Function to input polynomial coefficients from user
template<typename PolynomialType>
PolynomialType inputPolynomial() {
    int degree;
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coeffs(degree + 1);
    std::cout << "Enter the coefficients (from highest to lowest degree):\n";
    for (int i = degree; i >= 0; i--) {
        std::cout << "Coefficient of x^" << i << ": ";
        std::cin >> coeffs[i];
    }
    return PolynomialType(coeffs);
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nPolynomial Operations Menu:\n";
    std::cout << "1. Add two polynomials\n";
    std::cout << "2. Subtract two polynomials\n";
    std::cout << "3. Multiply two polynomials\n";
    std::cout << "4. Evaluate polynomial at a given value\n";
    std::cout << "5. Find the derivative of a polynomial\n";
    std::cout << "6. Find the integral of a polynomial\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

template<typename PolynomialType>
void handleOperations() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialType p1 = inputPolynomial<PolynomialType>();
                std::cout << "Enter the second polynomial:\n";
                PolynomialType p2 = inputPolynomial<PolynomialType>();
                PolynomialType sum = p1 + p2;
                std::cout << "Result of addition: " << sum << "\n";
                break;
            }
            case 2: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialType p1 = inputPolynomial<PolynomialType>();
                std::cout << "Enter the second polynomial:\n";
                PolynomialType p2 = inputPolynomial<PolynomialType>();
                PolynomialType diff = p1 - p2;
                std::cout << "Result of subtraction: " << diff << "\n";
                break;
            }
            case 3: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialType p1 = inputPolynomial<PolynomialType>();
                std::cout << "Enter the second polynomial:\n";
                PolynomialType p2 = inputPolynomial<PolynomialType>();
                PolynomialType product = p1 * p2;
                std::cout << "Result of multiplication: " << product << "\n";
                break;
            }
            case 4: {
                std::cout << "Enter the polynomial:\n";
                PolynomialType p = inputPolynomial<PolynomialType>();
                double x;
                std::cout << "Enter the value of x: ";
                std::cin >> x;
                double result = p.evaluate(x);
                std::cout << "Result of evaluation at x = " << x << ": " << result << "\n";
                break;
            }
            case 5: {
                std::cout << "Enter the polynomial:\n";
                PolynomialType p = inputPolynomial<PolynomialType>();
                PolynomialType deriv = p.derivative();
                std::cout << "Derivative of the polynomial: " << deriv << "\n";
                break;
            }
            case 6: {
                std::cout << "Enter the polynomial:\n";
                PolynomialType p = inputPolynomial<PolynomialType>();
                PolynomialType integ = p.integral();
                std::cout << "Integral of the polynomial: " << integ << " + C\n";
                break;
            }
            case 7:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 7);
}

int main() {
    int polyChoice;
    std::cout << "Which polynomial type would you like to work with?\n";
    std::cout << "1. PolynomialWithChatGPT\n";
    std::cout << "2. PolynomialWithCopiolt\n";
    std::cout << "Enter your choice: ";
    std::cin >> polyChoice;

    if (polyChoice == 1) {
        handleOperations<PolynomialWithChatGPT>();
    } else if (polyChoice == 2) {
        handleOperations<PolynomialWithCopiolt>();
    } else {
        std::cout << "Invalid polynomial type choice.\n";
    }

    return 0;
}
