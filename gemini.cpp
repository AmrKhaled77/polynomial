//
// Created by a on 10/12/2024.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class PolynomialWIthGemini {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    PolynomialWIthGemini() : coeffs(1, 0) {} // Default constructor: initializes to zero polynomial
    PolynomialWIthGemini(int coefficients) : coeffs(coefficients) {}
    PolynomialWIthGemini(const PolynomialWIthGemini& other) : coeffs(other.coeffs) {}

    // Destructor (optional)
    ~PolynomialWIthGemini() {}

    // Assignment operator
    PolynomialWIthGemini& operator=(const PolynomialWIthGemini& other) {
        coeffs = other.coeffs;
        return *this;
    }

    // Arithmetic operators
    PolynomialWIthGemini operator+(const PolynomialWIthGemini& other) const {
        int maxDegree = max(degree(), other.degree());
        PolynomialWIthGemini result(maxDegree + 1);
        for (int i = 0; i <= maxDegree; ++i) {
            result.coeffs[i] = coeffs[i] + other.coeffs[i];
        }
        return result;
    }

    PolynomialWIthGemini operator-(const PolynomialWIthGemini& other) const {
        PolynomialWIthGemini result(other.degree());
        for (int i = 0; i <= other.degree(); ++i) {
            result.coeffs[i] = -other.coeffs[i];
        }
        return result;
    }

    PolynomialWIthGemini operator*(const PolynomialWIthGemini& other) const {
        int newDegree = degree() + other.degree();
        PolynomialWIthGemini result(newDegree + 1);
        for (int i = 0; i <= degree(); ++i) {
            for (int j = 0; j <= other.degree(); ++j) {
                result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return result;
    }

    // Equality operator
    bool operator==(const PolynomialWIthGemini& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const PolynomialWIthGemini& poly) {
        for (int i = poly.degree(); i >= 0; --i) {
            if (poly.coeffs[i] != 0) {
                if (i > 1) {
                    out << poly.coeffs[i] << "x^" << i;
                } else if (i == 1) {
                    out << poly.coeffs[i] << "x";
                } else {
                    out << poly.coeffs[i];
                }
                if (i > 0) {
                    out << " + ";
                }
            }
        }
        return out;
    }

    // Utility functions
    int degree() const {
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            if (coeffs[i] != 0) {
                return i;
            }
        }
        return -1; // Empty polynomial
    }

    double evaluate(double x) const {
        double result = 0;
        for (int i = degree(); i >= 0; --i) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    PolynomialWIthGemini compose(const PolynomialWIthGemini& q) const {
        // Implement composition using Horner's method or other efficient algorithms
        // ...
    }

    PolynomialWIthGemini derivative() const {
        if (degree() == 0) {
            return PolynomialWIthGemini(); // Zero polynomial
        }
        PolynomialWIthGemini result(degree() - 1);
        for (int i = 1; i <= degree(); ++i) {
            result.coeffs[i - 1] = coeffs[i] * i;
        }
        return result;
    }

    PolynomialWIthGemini integral() const {
        PolynomialWIthGemini result(degree() + 1);
        result.coeffs[0] = 0; // Constant term of integral
        for (int i = 0; i <= degree(); ++i) {
            result.coeffs[i + 1] = coeffs[i] / (i + 1);
        }
        return result;
    }

    double integral(double x1, double x2) const {
        return integral().evaluate(x2) - integral().evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) {
        // Implement root-finding algorithm (e.g., Newton-Raphson, bisection)
        // ...
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const {
        if (degree < 0 || degree >= coeffs.size()) {
            return 0; // Coefficient of non-existent degree
        }
        return coeffs[degree];
    }
};