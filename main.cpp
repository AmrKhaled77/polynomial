#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;




class PolynomialWithChatGPT {
private:
    vector<double> coeffs;  // Store coefficients of the polynomial

public:

    // Constructors
    PolynomialWithChatGPT() {}
    PolynomialWithChatGPT(const vector<double>& coefficients) : coeffs(coefficients) {}
    PolynomialWithChatGPT(const PolynomialWithChatGPT& other) : coeffs(other.coeffs) {}

    // Destructor
    ~PolynomialWithChatGPT() {}

    // Assignment operator
    PolynomialWithChatGPT& operator=(const PolynomialWithChatGPT& other) {
        if (this != &other) {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    PolynomialWithChatGPT operator+(const PolynomialWithChatGPT& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (size_t i = 0; i < coeffs.size(); i++) result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); i++) result[i] += other.coeffs[i];
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT operator-(const PolynomialWithChatGPT& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0);
        for (size_t i = 0; i < coeffs.size(); i++) result[i] += coeffs[i];
        for (size_t i = 0; i < other.coeffs.size(); i++) result[i] -= other.coeffs[i];
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT operator*(const PolynomialWithChatGPT& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0);
        for (size_t i = 0; i < coeffs.size(); i++) {
            for (size_t j = 0; j < other.coeffs.size(); j++) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return PolynomialWithChatGPT(result);
    }

    // Equality operator
    bool operator==(const PolynomialWithChatGPT& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const PolynomialWithChatGPT& poly) {
        for (int i = poly.coeffs.size() - 1; i >= 0; i--) {
            out << poly.coeffs[i];
            if (i != 0) out << "x^" << i << " + ";
        }
        return out;
    }

    // Utility functions
    int degree() const {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const {
        double result = 0;
        for (int i = coeffs.size() - 1; i >= 0; i--) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    PolynomialWithChatGPT compose(const PolynomialWithChatGPT& q) const {
        PolynomialWithChatGPT result({0});
        for (int i = coeffs.size() - 1; i >= 0; i--) {
            result = result * q + PolynomialWithChatGPT({coeffs[i]});
        }
        return result;
    }

    PolynomialWithChatGPT derivative() const {
        vector<double> result;
        for (int i = 1; i < coeffs.size(); i++) {
            result.push_back(i * coeffs[i]);
        }
        return PolynomialWithChatGPT(result);
    }

    PolynomialWithChatGPT integral() const {
        vector<double> result(coeffs.size() + 1, 0);
        for (int i = 0; i < coeffs.size(); i++) {
            result[i + 1] = coeffs[i] / (i + 1);
        }
        return PolynomialWithChatGPT(result);
    }

    double integral(double x1, double x2) const {
        PolynomialWithChatGPT intPoly = this->integral();
        return intPoly.evaluate(x2) - intPoly.evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) {
        PolynomialWithChatGPT deriv = this->derivative();
        double x = guess;
        for (int i = 0; i < maxIter; i++) {
            double fx = this->evaluate(x);
            if (abs(fx) < tolerance) return x;
            double fpx = deriv.evaluate(x);
            if (fpx == 0) break;
            x = x - fx / fpx;
        }
        return x;
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const {
        if (degree < coeffs.size()) return coeffs[degree];
        return 0;
    }
};


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;








int main() {
    // Test case 1: Addition of two polynomials


    vector<double> coeffs1 = {1, 2, 3};  // 3x^2 + 2x + 1
    vector<double> coeffs2 = {4, 5};     // 5x + 4
    PolynomialWithChatGPT poly1(coeffs1);
    PolynomialWithChatGPT poly2(coeffs2);

    PolynomialWithChatGPT result = poly1 + poly2;
    cout << "Caht_GPT Test case 1: " << result << endl;  // Expected: 3x^2 + 7x + 5

    // Test case 2: Subtraction of two polynomials
    result = poly1 - poly2;
    cout << "Caht_GPT Test case 2: " << result << endl;  // Expected: 3x^2 - 3x - 3

    // Test case 3: Multiplication of two polynomials
    result = poly1 * poly2;
    cout << "Caht_GPT Test case 3: " << result << endl;  // Expected: 15x^3 + 23x^2 + 13x + 4

    // Test case 4: Evaluation of a polynomial at x = 1
    double value = poly1.evaluate(1);
    cout << "Caht_GPT Test case 4: " << value << endl;  // Expected: 6

    // Test case 5: Evaluation of a polynomial at x = 0
    value = poly2.evaluate(0);
    cout << "Caht_GPT Test case 5: " << value << endl;  // Expected: 4

    // Test case 6: Derivative of a polynomial
    PolynomialWithChatGPT derivative = poly1.derivative();
    cout << "Caht_GPT Test case 6: " << derivative << endl;  // Expected: 6x + 2

    // Test case 7: Integral of a polynomial
    PolynomialWithChatGPT integral = poly1.integral();
    cout << "Caht_GPT Test case 7: " << integral << endl;  // Expected: x^3 + x^2 + x + C

    // Test case 8: Root of a quadratic polynomial GPT
    PolynomialWithChatGPT quadratic({2, -3, 1});  // x^2 - 3x + 2
    double root = quadratic.getRoot(1);
    cout << "Caht_GPT Test case 8: " << root << endl;  // Expected: around 1

    // Test case 9: Root of a linear polynomial GPT
    PolynomialWithChatGPT linear({1, -5});  // x - 5
    root = linear.getRoot(1);
    cout << "Caht_GPT Test case 9: " << root << endl;  // Expected: 5

    // Test case 10: Zero polynomial evaluation
    PolynomialWithChatGPT zeroPoly({0, 0, 0});
    value = zeroPoly.evaluate(3);
    cout << "Caht_GPT Test case 10: " << value << endl;  // Expected: 0

    // Test case 11: Adding a zero polynomial
    result = poly1 + zeroPoly;
    cout << "Caht_GPT Test case 11: " << result << endl;  // Expected: 3x^2 + 2x + 1

    // Test case 12: Subtracting a zero polynomial
    result = poly1 - zeroPoly;
    cout << "Caht_GPT Test case 12: " << result << endl;  // Expected: 3x^2 + 2x + 1

    // Test case 13: Multiplying by zero polynomial
    result = poly1 * zeroPoly;
    cout << "Caht_GPT Test case 13: " << result << endl;  // Expected: 0

    // Test case 14: Compose two polynomials GPT
    PolynomialWithChatGPT p1({1, 2});  // 2x + 1
    PolynomialWithChatGPT p2({0, 1});  // x
    result = p1.compose(p2);
    cout << "Caht_GPT Test case 14: " << result << endl;  // Expected: 2x + 1

    // Test case 15: Degree of a polynomial
    int degree = poly1.degree();
    cout << "Caht_GPT Test case 15: " << degree << endl;  // Expected: 2

    // Test case 16: Integral of a polynomial over an interval GPT
    double integralValue = poly1.integral(0, 1);
    cout << "Caht_GPT Test case 16: " << integralValue << endl;  // Integral result

    // Test case 17: Testing equality of two polynomials
    bool isEqual = (poly1 == poly2);
    cout << "Caht_GPT Test case 17: " << isEqual << endl;  // Expected: false

    // Test case 18: Testing equality of a polynomial with itself
    isEqual = (poly1 == poly1);
    cout << "Caht_GPT Test case 18: " << isEqual << endl;  // Expected: true

    // Test case 19: Setting coefficients of a polynomial
    PolynomialWithChatGPT poly3;
    poly3.setCoefficients({3, 4, 5});
    cout << "Caht_GPT Test case 19: " << poly3 << endl;  // Expected: 5x^2 + 4x + 3

    // Test case 20: Getting a specific coefficient
    double coeff = poly1.getCoefficient(2);
    cout << "Caht_GPT Test case 20: " << coeff << endl;  // Expected: 3

    // Test case 21: Getting coefficient out of bounds
    coeff = poly1.getCoefficient(5);
    cout << "Caht_GPT Test case 21: " << coeff << endl;  // Expected: 0 or null el a7sen ytpa3 resala

    // Test case 22: Add polynomials of different lengths
    PolynomialWithChatGPT shortPoly({1, 2});   // 2x + 1
    PolynomialWithChatGPT longPoly({1, 2, 3, 4}); // 4x^3 + 3x^2 + 2x + 1
    result = shortPoly + longPoly;
    cout << "Caht_GPT Test case 22: " << result << endl;  // Expected: 4x^3 + 3x^2 + 4x + 2

    // Test case 23: Subtract polynomials of different lengths
    result = longPoly - shortPoly;
    cout << "Caht_GPT Test case 23: " << result << endl;  // Expected: 4x^3 + 3x^2 + 0x + 0

    // Test case 24: Multiplying by a constant polynomial
    PolynomialWithChatGPT constantPoly({2});  // 2
    result = poly1 * constantPoly;
    cout << "Caht_GPT Test case 24: " << result << endl;  // Expected: 6x^2 + 4x + 2

    // Test case 25: Derivative of a constant polynomial
    PolynomialWithChatGPT constantPoly5({5});  // 5
    derivative = constantPoly5.derivative();
    cout << "Caht_GPT Test case 25: " << derivative << endl;  // Expected: 0

    // Test case 26: Root finding for non-root polynomial GPT
    double nonRoot = constantPoly5.getRoot();
    cout << "Caht_GPT Test case 26: " << nonRoot << endl;  // Expected: NaN or no root

    // Test case 27: PolynomialWIthGemini evaluation for a negative x GPT
    value = poly1.evaluate(-2);
    cout << "Caht_GPT Test case 27: " << value << endl;  // Varies based on the polynomial

    // Test case 28: Finding roots for non-trivial polynomials GPT
    PolynomialWithChatGPT cubic({-6, 11, -6, 1});  // x^3 - 6x^2 + 11x - 6
    root = cubic.getRoot(1);
    cout << "Caht_GPT Test case 28: " << root << endl;  // Approximation of a root near 1

    // Test case 29: Add negative polynomials
    PolynomialWithChatGPT negPoly({-1, -2, -3});  // -3x^2 - 2x - 1
    result = poly1 + negPoly;
    cout << "Caht_GPT Test case 29: " << result << endl;  // PolynomialWIthGemini subtraction result

    // Test case 30: Subtract negative polynomials
    result = poly1 - negPoly;
    cout << "Caht_GPT Test case 30: " << result << endl;  // PolynomialWIthGemini addition result
}
