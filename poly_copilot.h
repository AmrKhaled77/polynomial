#ifndef POLYNOMIALWITHCOPIOLT_H
#define POLYNOMIALWITHCOPIOLT_H

#include <iostream>
#include <vector>

class PolynomialWithCopiolt
{
private:
    std::vector<double> coeffs;

public:
    // Constructors
    PolynomialWithCopiolt();
    PolynomialWithCopiolt(const std::vector<double> coefficients);
    PolynomialWithCopiolt(const PolynomialWithCopiolt &other);

    // Destructor
    ~PolynomialWithCopiolt();

    // Assignment operator
    PolynomialWithCopiolt &operator=(const PolynomialWithCopiolt &other);

    // Arithmetic operators
    PolynomialWithCopiolt operator+(const PolynomialWithCopiolt &other) const;
    PolynomialWithCopiolt operator-(const PolynomialWithCopiolt &other) const;
    PolynomialWithCopiolt operator*(const PolynomialWithCopiolt &other) const;

    // Equality operator
    bool operator==(const PolynomialWithCopiolt &other) const;

    // Output operator
    friend std::ostream &operator<<(std::ostream &out, const PolynomialWithCopiolt &poly);

    // Utility functions
    int degree() const;
    double evaluate(double x) const;
    PolynomialWithCopiolt compose(const PolynomialWithCopiolt &q) const;
    PolynomialWithCopiolt derivative() const;
    PolynomialWithCopiolt integral() const;
    double integral(double x1, double x2) const;
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100);

    // Getters and Setters
    void setCoefficients(const std::vector<double> &coefficients);
    double getCoefficient(int degree) const;
};

#endif // POLYNOMIALWITHCOPIOLT_H
