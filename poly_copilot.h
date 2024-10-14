#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class PolynomialWithCopiolt
{
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    PolynomialWithCopiolt() : coeffs({0.0}) {}

    PolynomialWithCopiolt(const vector<double> coefficients) : coeffs(coefficients) {}

    PolynomialWithCopiolt(const PolynomialWithCopiolt &other) : coeffs(other.coeffs) {}

    // Destructor
    ~PolynomialWithCopiolt() {}

    // Assignment operator
    PolynomialWithCopiolt &operator=(const PolynomialWithCopiolt &other)
    {
        if (this != &other)
        {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    PolynomialWithCopiolt operator+(const PolynomialWithCopiolt &other) const
    {
        vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0.0);

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

    PolynomialWithCopiolt operator-(const PolynomialWithCopiolt &other) const
    {
        vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0.0);

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

    PolynomialWithCopiolt operator*(const PolynomialWithCopiolt &other) const
    {
        vector<double> result_coeffs(coeffs.size() + other.coeffs.size() - 1, 0.0);

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
    bool operator==(const PolynomialWithCopiolt &other) const
    {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream &operator<<(ostream &out, const PolynomialWithCopiolt &poly)
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
    int degree() const
    {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const
    {
        double result = 0.0;
        for (int i = coeffs.size() - 1; i >= 0; --i)
        {
            result = result * x + coeffs[i];
        }
        return result;
    }

    PolynomialWithCopiolt compose(const PolynomialWithCopiolt &q) const
    {
        PolynomialWithCopiolt result;
        for (int i = coeffs.size() - 1; i >= 0; --i)
        {
            result = result * q + PolynomialWithCopiolt(vector<double>{coeffs[i]});
        }
        return result;
    }

    PolynomialWithCopiolt derivative() const
    {
        vector<double> result_coeffs;
        for (int i = 1; i < coeffs.size(); ++i)
        {
            result_coeffs.push_back(coeffs[i] * i);
        }
        return PolynomialWithCopiolt(result_coeffs);
    }

    PolynomialWithCopiolt integral() const
    {
        vector<double> result_coeffs(1, 0.0); // C is constant of integration
        for (int i = 0; i < coeffs.size(); ++i)
        {
            result_coeffs.push_back(coeffs[i] / (i + 1));
        }
        return PolynomialWithCopiolt(result_coeffs);
    }

    double integral(double x1, double x2) const
    {
        PolynomialWithCopiolt integral_poly = this->integral();
        return integral_poly.evaluate(x2) - integral_poly.evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100)
    {
        double x0 = guess;
        for (int i = 0; i < maxIter; ++i)
        {
            double fx = evaluate(x0);
            double dfx = derivative().evaluate(x0);
            if (fabs(dfx) < tolerance)
            {
                break;
            }
            double x1 = x0 - fx / dfx;
            if (fabs(x1 - x0) < tolerance)
            {
                return x1;
            }
            x0 = x1;
        }
        return x0;
    }

    void setCoefficients(const vector<double> &coefficients)
    {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const
    {
        if (degree < coeffs.size())
        {
            return coeffs[degree];
        }
        return 0.0;
    }
};
