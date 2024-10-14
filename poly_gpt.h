#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class PolynomialWithChatGPT
{
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    PolynomialWithChatGPT() {}
    PolynomialWithChatGPT(const vector<double> &coefficients) : coeffs(coefficients) {}
    PolynomialWithChatGPT(const PolynomialWithChatGPT &other) : coeffs(other.coeffs) {}

    // Destructor
    ~PolynomialWithChatGPT() {}

    // Assignment operator
    PolynomialWithChatGPT &operator=(const PolynomialWithChatGPT &other)
    {
        if (this != &other)
        {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    PolynomialWithChatGPT operator+(const PolynomialWithChatGPT &other) const
    {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (size_t i = 0; i < coeffs.size(); i++)
            result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); i++)
            result[i] += other.coeffs[i];
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT operator-(const PolynomialWithChatGPT &other) const
    {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (size_t i = 0; i < coeffs.size(); i++)
            result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); i++)
            result[i] -= other.coeffs[i];
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT operator*(const PolynomialWithChatGPT &other) const
    {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
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
    bool operator==(const PolynomialWithChatGPT &other) const
    {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream &operator<<(ostream &out, const PolynomialWithChatGPT &poly)
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
    int degree() const
    {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const
    {
        double result = 0;
        for (int i = coeffs.size() - 1; i >= 0; i--)
        {
            result = result * x + coeffs[i];
        }
        return result;
    }

    PolynomialWithChatGPT compose(const PolynomialWithChatGPT &q) const
    {
        PolynomialWithChatGPT result({0});
        for (int i = coeffs.size() - 1; i >= 0; i--)
        {
            result = result * q + PolynomialWithChatGPT({coeffs[i]});
        }
        return result;
    }

    PolynomialWithChatGPT derivative() const
    {
        vector<double> result;
        for (int i = 1; i < coeffs.size(); i++)
        {
            result.push_back(i * coeffs[i]);
        }
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT integral() const
    {
        vector<double> result(coeffs.size() + 1, 0);
        for (int i = 0; i < coeffs.size(); i++)
        {
            result[i + 1] = coeffs[i] / (i + 1);
        }
        return PolynomialWithChatGPT(result);
    }

    double integral(double x1, double x2) const
    {
        PolynomialWithChatGPT intPoly = this->integral();
        return intPoly.evaluate(x2) - intPoly.evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100)
    {
        PolynomialWithChatGPT deriv = this->derivative();
        double x = guess;
        for (int i = 0; i < maxIter; i++)
        {
            double fx = this->evaluate(x);
            if (abs(fx) < tolerance)
                return x;
            double fpx = deriv.evaluate(x);
            if (fpx == 0)
                break;
            x = x - fx / fpx;
        }
        return x;
    }

    void setCoefficients(const vector<double> &coefficients)
    {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const
    {
        if (degree < coeffs.size())
            return coeffs[degree];
        return 0;
    }
};

