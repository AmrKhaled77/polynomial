#include "poly_copilot.h"
#include <cmath>
#include <algorithm>

// Constructors
PolynomialWithCopiolt::PolynomialWithCopiolt() : coeffs({0.0}) {}

PolynomialWithCopiolt::PolynomialWithCopiolt(const std::vector<double> coefficients) : coeffs(coefficients) {}

PolynomialWithCopiolt::PolynomialWithCopiolt(const PolynomialWithCopiolt &other) : coeffs(other.coeffs) {}

// Destructor
PolynomialWithCopiolt::~PolynomialWithCopiolt() {}

// Assignment operator
PolynomialWithCopiolt &PolynomialWithCopiolt::operator=(const PolynomialWithCopiolt &other)
{
    if (this != &other)
    {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
PolynomialWithCopiolt PolynomialWithCopiolt::operator+(const PolynomialWithCopiolt &other) const
{
    std::vector<double> result_coeffs(std::max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
    {
        result_coeffs[i] += coeffs[i];
    }

    for (size_t i = 0; i < other.coeffs.size(); ++i)
    {
        result_coeffs[i] += other.coeffs[i];
    }

    return PolynomialWithCopiolt(result_coeffs);
}

PolynomialWithCopiolt PolynomialWithCopiolt::operator-(const PolynomialWithCopiolt &other) const
{
    std::vector<double> result_coeffs(std::max(coeffs.size(), other.coeffs.size()), 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
    {
        result_coeffs[i] += coeffs[i];
    }

    for (size_t i = 0; i < other.coeffs.size(); ++i)
    {
        result_coeffs[i] -= other.coeffs[i];
    }

    return PolynomialWithCopiolt(result_coeffs);
}

PolynomialWithCopiolt PolynomialWithCopiolt::operator*(const PolynomialWithCopiolt &other) const
{
    std::vector<double> result_coeffs(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i)
    {
        for (size_t j = 0; j < other.coeffs.size(); ++j)
        {
            result_coeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    return PolynomialWithCopiolt(result_coeffs);
}

// Equality operator
bool PolynomialWithCopiolt::operator==(const PolynomialWithCopiolt &other) const
{
    return coeffs == other.coeffs;
}

// Output operator
std::ostream &operator<<(std::ostream &out, const PolynomialWithCopiolt &poly)
{
    for (int i = poly.coeffs.size() - 1; i >= 0; --i)
    {
        if (poly.coeffs[i] != 0)
        {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0)
            {
                out << "+";
            }
            out << poly.coeffs[i];
            if (i > 0)
            {
                out << "x^" << i << " ";
            }
        }
    }
    return out;
}

// Utility functions
int PolynomialWithCopiolt::degree() const
{
    return coeffs.size() - 1;
}

double PolynomialWithCopiolt::evaluate(double x) const
{
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i)
    {
        result = result * x + coeffs[i];
    }
    return result;
}

PolynomialWithCopiolt PolynomialWithCopiolt::compose(const PolynomialWithCopiolt &q) const
{
    PolynomialWithCopiolt result;
    for (int i = coeffs.size() - 1; i >= 0; --i)
    {
        result = result * q + PolynomialWithCopiolt(std::vector<double>{coeffs[i]});
    }
    return result;
}

PolynomialWithCopiolt PolynomialWithCopiolt::derivative() const
{
    std::vector<double> result_coeffs;
    for (int i = 1; i < coeffs.size(); ++i)
    {
        result_coeffs.push_back(coeffs[i] * i);
    }
    return PolynomialWithCopiolt(result_coeffs);
}

PolynomialWithCopiolt PolynomialWithCopiolt::integral() const
{
    std::vector<double> result_coeffs(1, 0.0); // C is constant of integration
    for (int i = 0; i < coeffs.size(); ++i)
    {
        result_coeffs.push_back(coeffs[i] / (i + 1));
    }
    return PolynomialWithCopiolt(result_coeffs);
}

double PolynomialWithCopiolt::integral(double x1, double x2) const
{
    PolynomialWithCopiolt integral_poly = this->integral();
    return integral_poly.evaluate(x2) - integral_poly.evaluate(x1);
}

double PolynomialWithCopiolt::getRoot(double guess, double tolerance, int maxIter)
{
    double x0 = guess;
    for (int i = 0; i < maxIter; ++i)
    {
        double fx = evaluate(x0);
        double dfx = derivative().evaluate(x0);
        if (std::fabs(dfx) < tolerance)
        {
            break;
        }
        double x1 = x0 - fx / dfx;
        if (std::fabs(x1 - x0) < tolerance)
        {
            return x1;
        }
        x0 = x1;
    }
    return x0;
}

// Getters and Setters
void PolynomialWithCopiolt::setCoefficients(const std::vector<double> &coefficients)
{
    coeffs = coefficients;
}

double PolynomialWithCopiolt::getCoefficient(int degree) const
{
    if (degree < coeffs.size())
    {
        return coeffs[degree];
    }
    return 0.0;
}
// Function to input polynomial coefficients from user
PolynomialWithCopiolt inputPolynomial() {
    int degree;
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coeffs(degree + 1);
    std::cout << "Enter the coefficients (from highest to lowest degree):\n";
    for (int i = degree; i >= 0; i--) {
        std::cout << "Coefficient of x^" << i << ": ";
        std::cin >> coeffs[i];
    }
    return PolynomialWithCopiolt(coeffs);
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
                PolynomialWithCopiolt p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithCopiolt p2 = inputPolynomial();
                PolynomialWithCopiolt sum = p1 + p2;
                std::cout << "Result of addition: " << sum << "\n";
                break;
            }
            case 2: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialWithCopiolt p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithCopiolt p2 = inputPolynomial();
                PolynomialWithCopiolt diff = p1 - p2;
                std::cout << "Result of subtraction: " << diff << "\n";
                break;
            }
            case 3: {
                std::cout << "Enter the first polynomial:\n";
                PolynomialWithCopiolt p1 = inputPolynomial();
                std::cout << "Enter the second polynomial:\n";
                PolynomialWithCopiolt p2 = inputPolynomial();
                PolynomialWithCopiolt product = p1 * p2;
                std::cout << "Result of multiplication: " << product << "\n";
                break;
            }
            case 4: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithCopiolt p = inputPolynomial();
                double x;
                std::cout << "Enter the value of x: ";
                std::cin >> x;
                double result = p.evaluate(x);
                std::cout << "Result of evaluation at x = " << x << ": " << result << "\n";
                break;
            }
            case 5: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithCopiolt p = inputPolynomial();
                PolynomialWithCopiolt deriv = p.derivative();
                std::cout << "Derivative of the polynomial: " << deriv << "\n";
                break;
            }
            case 6: {
                std::cout << "Enter the polynomial:\n";
                PolynomialWithCopiolt p = inputPolynomial();
                PolynomialWithCopiolt integ = p.integral();
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

