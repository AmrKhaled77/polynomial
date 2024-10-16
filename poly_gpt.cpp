#include "poly_gpt.h"
#include <cmath>
#include <algorithm>

// Constructors
PolynomialWithChatGPT::PolynomialWithChatGPT() {}

PolynomialWithChatGPT::PolynomialWithChatGPT(const std::vector<double> &coefficients) : coeffs(coefficients) {}

PolynomialWithChatGPT::PolynomialWithChatGPT(const PolynomialWithChatGPT &other) : coeffs(other.coeffs) {}

// Destructor
PolynomialWithChatGPT::~PolynomialWithChatGPT() {}

// Assignment operator
PolynomialWithChatGPT &PolynomialWithChatGPT::operator=(const PolynomialWithChatGPT &other)
{
    if (this != &other)
    {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
PolynomialWithChatGPT PolynomialWithChatGPT::operator+(const PolynomialWithChatGPT &other) const
{
    std::vector<double> result(std::max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); i++)
        result[i] += coeffs[i];
    for (size_t i = 0; i < other.coeffs.size(); i++)
        result[i] += other.coeffs[i];
    return PolynomialWithChatGPT(result);
}

PolynomialWithChatGPT PolynomialWithChatGPT::operator-(const PolynomialWithChatGPT &other) const
{
    std::vector<double> result(std::max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); i++)
        result[i] += coeffs[i];
    for (size_t i = 0; i < other.coeffs.size(); i++)
        result[i] -= other.coeffs[i];
    return PolynomialWithChatGPT(result);
}

PolynomialWithChatGPT PolynomialWithChatGPT::operator*(const PolynomialWithChatGPT &other) const
{
    std::vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
    for (size_t i = 0; i < coeffs.size(); i++)
    {
        for (size_t j = 0; j < other.coeffs.size(); j++)
        {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return PolynomialWithChatGPT(result);
}

// Equality operator
bool PolynomialWithChatGPT::operator==(const PolynomialWithChatGPT &other) const
{
    return coeffs == other.coeffs;
}

// Output operator
std::ostream &operator<<(std::ostream &out, const PolynomialWithChatGPT &poly)
{
    for (int i = poly.coeffs.size() - 1; i >= 0; i--)
    {
        out << poly.coeffs[i];
        if (i != 0)
            out << "x^" << i << " + ";
    }
    return out;
}

// Utility functions
int PolynomialWithChatGPT::degree() const
{
    return coeffs.size() - 1;
}

double PolynomialWithChatGPT::evaluate(double x) const
{
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; i--)
    {
        result = result * x + coeffs[i];
    }
    return result;
}

PolynomialWithChatGPT PolynomialWithChatGPT::compose(const PolynomialWithChatGPT &q) const
{
    PolynomialWithChatGPT result({0});
    for (int i = coeffs.size() - 1; i >= 0; i--)
    {
        result = result * q + PolynomialWithChatGPT({coeffs[i]});
    }
    return result;
}

PolynomialWithChatGPT PolynomialWithChatGPT::derivative() const
{
    std::vector<double> result;
    for (int i = 1; i < coeffs.size(); i++)
    {
        result.push_back(i * coeffs[i]);
    }
    return PolynomialWithChatGPT(result);
}

PolynomialWithChatGPT PolynomialWithChatGPT::integral() const
{
    std::vector<double> result(coeffs.size() + 1, 0);
    for (int i = 0; i < coeffs.size(); i++)
    {
        result[i + 1] = coeffs[i] / (i + 1);
    }
    return PolynomialWithChatGPT(result);
}

double PolynomialWithChatGPT::integral(double x1, double x2) const
{
    PolynomialWithChatGPT intPoly = this->integral();
    return intPoly.evaluate(x2) - intPoly.evaluate(x1);
}

double PolynomialWithChatGPT::getRoot(double guess, double tolerance, int maxIter)
{
    PolynomialWithChatGPT deriv = this->derivative();
    double x = guess;
    for (int i = 0; i < maxIter; i++)
    {
        double fx = this->evaluate(x);
        if (std::abs(fx) < tolerance)
            return x;
        double fpx = deriv.evaluate(x);
        if (fpx == 0)
            break;
        x = x - fx / fpx;
    }
    return x;
}

// Getters and Setters
void PolynomialWithChatGPT::setCoefficients(const std::vector<double> &coefficients)
{
    coeffs = coefficients;
}

double PolynomialWithChatGPT::getCoefficient(int degree) const
{
    if (degree < coeffs.size())
        return coeffs[degree];
    return 0;
}
// Function to input polynomial coefficients from user
PolynomialWithChatGPT inputPolynomial() {
    int degree;
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coeffs(degree + 1);
    std::cout << "Enter the coefficients (from highest to lowest degree):\n";
    for (int i = degree; i >= 0; i--) {
        std::cout << "Coefficient of x^" << i << ": ";
        std::cin >> coeffs[i];
    }
    return PolynomialWithChatGPT(coeffs);
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

int main() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialWithChatGPT p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithChatGPT p2 = inputPolynomial();
                PolynomialWithChatGPT sum = p1 + p2;
                std::cout << "Result of addition: " << sum << "\n";
                break;
            }
            case 2: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialWithChatGPT p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithChatGPT p2 = inputPolynomial();
                PolynomialWithChatGPT diff = p1 - p2;
                std::cout << "Result of subtraction: " << diff << "\n";
                break;
            }
            case 3: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialWithChatGPT p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithChatGPT p2 = inputPolynomial();
                PolynomialWithChatGPT product = p1 * p2;
                std::cout << "Result of multiplication: " << product << "\n";
                break;
            }
            case 4: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithChatGPT p = inputPolynomial();
                double x;
                std::cout << "Enter the value of x: ";
                std::cin >> x;
                double result = p.evaluate(x);
                std::cout << "Result of evaluation at x = " << x << ": " << result << "\n";
                break;
            }
            case 5: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithChatGPT p = inputPolynomial();
                PolynomialWithChatGPT deriv = p.derivative();
                std::cout << "Derivative of the polynomial: " << deriv << "\n";
                break;
            }
            case 6: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithChatGPT p = inputPolynomial();
                PolynomialWithChatGPT integ = p.integral();
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

    return 0;
}

