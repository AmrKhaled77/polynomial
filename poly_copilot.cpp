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
