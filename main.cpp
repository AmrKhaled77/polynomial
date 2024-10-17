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






class PolynomialWithCopilot {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    PolynomialWithCopilot() : coeffs(1, 0.0) {} // Default constructor: polynomial = 0

    PolynomialWithCopilot(const vector<double>& coefficients) : coeffs(coefficients) {}

    PolynomialWithCopilot(const PolynomialWithCopilot& other) : coeffs(other.coeffs) {}

    // Destructor
    ~PolynomialWithCopilot() {}

    // Assignment operator
    PolynomialWithCopilot& operator=(const PolynomialWithCopilot& other) {
        if (this != &other) {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    PolynomialWithCopilot operator+(const PolynomialWithCopilot& other) const {
        size_t maxDegree = max(coeffs.size(), other.coeffs.size());
        vector<double> result(maxDegree, 0.0);

        for (size_t i = 0; i < maxDegree; ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] += other.coeffs[i];
        }
        return PolynomialWithCopilot(result);
    }

    PolynomialWithCopilot operator-(const PolynomialWithCopilot& other) const {
        size_t maxDegree = max(coeffs.size(), other.coeffs.size());
        vector<double> result(maxDegree, 0.0);

        for (size_t i = 0; i < maxDegree; ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
        }
        return PolynomialWithCopilot(result);
    }

    PolynomialWithCopilot operator*(const PolynomialWithCopilot& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);

        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); ++j) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return PolynomialWithCopilot(result);
    }

    // Equality operator
    bool operator==(const PolynomialWithCopilot& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const PolynomialWithCopilot& poly) {
        for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
            out << poly.coeffs[i];
            if (i > 0) out << "x^" << i << " + ";
        }
        return out;
    }

    // Utility functions
    int degree() const {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    PolynomialWithCopilot derivative() const {
        if (coeffs.size() <= 1) return PolynomialWithCopilot();

        vector<double> derivedCoeffs(coeffs.size() - 1);
        for (size_t i = 1; i < coeffs.size(); ++i) {
            derivedCoeffs[i - 1] = coeffs[i] * i;
        }
        return PolynomialWithCopilot(derivedCoeffs);
    }

    PolynomialWithCopilot integral() const {
        vector<double> integralCoeffs(coeffs.size() + 1, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i) {
            integralCoeffs[i + 1] = coeffs[i] / (i + 1);
        }
        return PolynomialWithCopilot(integralCoeffs);
    }

    double integral(double x1, double x2) const {
        PolynomialWithCopilot integrated = this->integral();
        return integrated.evaluate(x2) - integrated.evaluate(x1);
    }

    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) const {
        PolynomialWithCopilot deriv = this->derivative();
        double x = guess;
        for (int i = 0; i < maxIter; ++i) {
            double fx = this->evaluate(x);
            double fpx = deriv.evaluate(x);
            if (abs(fx) < tolerance) return x;
            x = x - fx / fpx;
        }
        throw runtime_error("Max iterations reached without finding root");
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const {
        if (degree >= 0 && degree < coeffs.size()) {
            return coeffs[degree];
        }
        return 0.0; // Return 0 if degree is out of bounds
    }

    PolynomialWithCopilot compose(const PolynomialWithCopilot& q) const {
        PolynomialWithCopilot result;
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            result = result * q + PolynomialWithCopilot(vector<double>{coeffs[i]});
        }
        return result;
    }
};







void runHardCodedTestCases(){
    vector<double> coeffs1 = {1, 2, 3}; // 3x^2 + 2x + 1
    vector<double> coeffs2 = {4, 5};    // 5x + 4
    PolynomialWithChatGPT poly1_gpt(coeffs1);
    PolynomialWithChatGPT poly2_gpt(coeffs2);

    PolynomialWithCopilot poly1_copilot(coeffs1);
    PolynomialWithCopilot poly2_copilot(coeffs2);

    PolynomialWithChatGPT result_gpt;
    PolynomialWithCopilot result_copilot;

    double value_gpt, value_copilot;

    // Test case 1: Addition of two polynomials
    result_gpt = poly1_gpt + poly2_gpt;
    result_copilot = poly1_copilot + poly2_copilot;
    cout << "Chat_GPT Test case 1 (Addition): " << result_gpt << endl;    // Expected: 3x^2 + 7x + 5
    cout << "Copilot Test case 1 (Addition): " << result_copilot << endl; // Expected: 3x^2 + 7x + 5

    // Test case 2: Subtraction of two polynomials
    result_gpt = poly1_gpt - poly2_gpt;
    result_copilot = poly1_copilot - poly2_copilot;
    cout << "Chat_GPT Test case 2 (Subtraction): " << result_gpt << endl;    // Expected: 3x^2 - 3x - 3
    cout << "Copilot Test case 2 (Subtraction): " << result_copilot << endl; // Expected: 3x^2 - 3x - 3

    // Test case 3: Multiplication of two polynomials
    result_gpt = poly1_gpt * poly2_gpt;
    result_copilot = poly1_copilot * poly2_copilot;
    cout << "Chat_GPT Test case 3 (Multiplication): " << result_gpt << endl;    // Expected: 15x^3 + 23x^2 + 13x + 4
    cout << "Copilot Test case 3 (Multiplication): " << result_copilot << endl; // Expected: 15x^3 + 23x^2 + 13x + 4

    // Test case 4: Evaluation of a polynomial at x = 1
    value_gpt = poly1_gpt.evaluate(1);
    value_copilot = poly1_copilot.evaluate(1);
    cout << "Chat_GPT Test case 4 (Evaluation at x=1): " << value_gpt << endl;    // Expected: 6
    cout << "Copilot Test case 4 (Evaluation at x=1): " << value_copilot << endl; // Expected: 6

    // Test case 5: Evaluation of a polynomial at x = 0
    value_gpt = poly2_gpt.evaluate(0);
    value_copilot = poly2_copilot.evaluate(0);
    cout << "Chat_GPT Test case 5 (Evaluation at x=0): " << value_gpt << endl;    // Expected: 4
    cout << "Copilot Test case 5 (Evaluation at x=0): " << value_copilot << endl; // Expected: 4

    // Test case 6: Derivative of a polynomial
    PolynomialWithChatGPT derivative_gpt = poly1_gpt.derivative();
    PolynomialWithCopilot derivative_copilot = poly1_copilot.derivative();
    cout << "Chat_GPT Test case 6 (Derivative): " << derivative_gpt << endl;    // Expected: 6x + 2
    cout << "Copilot Test case 6 (Derivative): " << derivative_copilot << endl; // Expected: 6x + 2

    // Test case 7: Integral of a polynomial
    PolynomialWithChatGPT integral_gpt = poly1_gpt.integral();
    PolynomialWithCopilot integral_copilot = poly1_copilot.integral();
    cout << "Chat_GPT Test case 7 (Integral): " << integral_gpt << endl;    // Expected: x^3 + x^2 + x + C
    cout << "Copilot Test case 7 (Integral): " << integral_copilot << endl; // Expected: x^3 + x^2 + x + C

    // Test case 8: Root of a quadratic polynomial
    PolynomialWithChatGPT quadratic_gpt({2, -3, 1}); // x^2 - 3x + 2
    PolynomialWithCopilot quadratic_copilot({2, -3, 1});
    double root_gpt = quadratic_gpt.getRoot(1);
    double root_copilot = quadratic_copilot.getRoot(1);
    cout << "Chat_GPT Test case 8 (Root of quadratic): " << root_gpt << endl;    // Expected: around 1
    cout << "Copilot Test case 8 (Root of quadratic): " << root_copilot << endl; // Expected: around 1

    // Test case 9: Root of a linear polynomial
    PolynomialWithChatGPT linear_gpt({1, -5}); // x - 5
    PolynomialWithCopilot linear_copilot({1, -5});
    root_gpt = linear_gpt.getRoot(1);
    root_copilot = linear_copilot.getRoot(1);
    cout << "Chat_GPT Test case 9 (Root of linear): " << root_gpt << endl;    // Expected: 5
    cout << "Copilot Test case 9 (Root of linear): " << root_copilot << endl; // Expected: 5

    // Test case 10: Definite Integral of a polynomial between two points (e.g., from x=0 to x=1)
    double definiteIntegral_gpt = poly1_gpt.integral(0, 1);
    double definiteIntegral_copilot = poly1_copilot.integral(0, 1);
    cout << "Chat_GPT Test case 10 (Definite Integral from 0 to 1): " << definiteIntegral_gpt << endl;    // Expected: 3.5
    cout << "Copilot Test case 10 (Definite Integral from 0 to 1): " << definiteIntegral_copilot << endl; // Expected: 3.5


    // Test case 11: Root finding for non-root polynomial
    PolynomialWithChatGPT constant_gpt({5}); // 5
    PolynomialWithCopilot constant_copilot({5});

    double nonRoot_gpt = constant_gpt.getRoot();
    double nonRoot_copilot = constant_copilot.getRoot();

    cout << "Chat_GPT Test case 26 (finding for non-root polynomial): " << nonRoot_gpt << endl;
    cout << "copilot Test case 26 (finding for non-root polynomial): " << nonRoot_copilot << endl;


    // Test case 12: Polynomial evaluated at negative values (e.g., x = -2)
    value_gpt = poly1_gpt.evaluate(-2);
    value_copilot = poly1_copilot.evaluate(-2);
    cout << "Chat_GPT Test case 12 (Evaluation at x=-2): " << value_gpt << endl;    // Expected: 7
    cout << "Copilot Test case 12 (Evaluation at x=-2): " << value_copilot << endl; // Expected: 7

    // Test case 13: Zero polynomial addition (e.g., poly1 + 0)
    vector<double> zero_coeffs = {0};
    PolynomialWithChatGPT zero_poly_gpt(zero_coeffs);
    PolynomialWithCopilot zero_poly_copilot(zero_coeffs);
    result_gpt = poly1_gpt + zero_poly_gpt;
    result_copilot = poly1_copilot + zero_poly_copilot;
    cout << "Chat_GPT Test case 13 (Addition with zero polynomial): " << result_gpt << endl;    // Expected: 3x^2 + 2x + 1
    cout << "Copilot Test case 13 (Addition with zero polynomial): " << result_copilot << endl; // Expected: 3x^2 + 2x + 1

    // Test case 14: Subtracting the zero polynomial from another polynomial (poly1 - 0)
    result_gpt = poly1_gpt - zero_poly_gpt;
    result_copilot = poly1_copilot - zero_poly_copilot;
    cout << "Chat_GPT Test case 14 (Subtraction with zero polynomial): " << result_gpt << endl;    // Expected: 3x^2 + 2x + 1
    cout << "Copilot Test case 14 (Subtraction with zero polynomial): " << result_copilot << endl; // Expected: 3x^2 + 2x + 1

    // Test case 15: Polynomial multiplied by zero polynomial (poly1 * 0)
    result_gpt = poly1_gpt * zero_poly_gpt;
    result_copilot = poly1_copilot * zero_poly_copilot;
    cout << "Chat_GPT Test case 15 (Multiplication with zero polynomial): " << result_gpt << endl;    // Expected: 0
    cout << "Copilot Test case 15 (Multiplication with zero polynomial): " << result_copilot << endl; // Expected: 0

    // Test case 16: Adding polynomials with different degrees

    vector<double> coeffs3 = {1, 0, 5}; // 5x^2 + 1
    PolynomialWithChatGPT poly3_gpt(coeffs3);
    PolynomialWithCopilot poly3_copilot(coeffs3);
    result_gpt = poly1_gpt + poly3_gpt;
    result_copilot = poly1_copilot + poly3_copilot;
    cout << "Chat_GPT Test case 16 (Addition with different degrees): " << result_gpt << endl;    // Expected: 8x^2 + 2x + 2
    cout << "Copilot Test case 16 (Addition with different degrees): " << result_copilot << endl; // Expected: 8x^2 + 2x + 2

    // Test case 17: Subtracting polynomials with different degrees
    result_gpt = poly1_gpt - poly3_gpt;
    result_copilot = poly1_copilot - poly3_copilot;
    cout << "Chat_GPT Test case 17 (Subtraction with different degrees): " << result_gpt << endl;    // Expected: -2x^2 + 2x
    cout << "Copilot Test case 17 (Subtraction with different degrees): " << result_copilot << endl; // Expected: -2x^2 + 2x

    // Test case 18: Multiplying polynomials with different degrees
    result_gpt = poly1_gpt * poly3_gpt;
    result_copilot = poly1_copilot * poly3_copilot;
    cout << "Chat_GPT Test case 18 (Multiplication with different degrees): " << result_gpt << endl;    // Expected: 15x^4 + 10x^3 + 11x^2 + 2x + 1
    cout << "Copilot Test case 18 (Multiplication with different degrees): " << result_copilot << endl; // Expected: 15x^4 + 10x^3 + 11x^2 + 2x + 1

    // Test case 19: Derivative of a linear polynomial
    PolynomialWithChatGPT linear_gpt2({5, -3}); // 5x - 3
    PolynomialWithCopilot linear_copilot2({5, -3});
    derivative_gpt = linear_gpt2.derivative();
    derivative_copilot = linear_copilot2.derivative();
    cout << "Chat_GPT Test case 19 (Derivative of linear polynomial): " << derivative_gpt << endl;    // Expected: 5
    cout << "Copilot Test case 19 (Derivative of linear polynomial): " << derivative_copilot << endl; // Expected: 5

    // Test case 20: Evaluate a higher degree polynomial (x^4 + 2x^3 + 3x^2 + 4x + 5) at x=2
    PolynomialWithChatGPT higher_deg_gpt({5, 4, 3, 2, 1}); // x^4 + 2x^3 + 3x^2 + 4x + 5
    PolynomialWithCopilot higher_deg_copilot({5, 4, 3, 2, 1});
    value_gpt = higher_deg_gpt.evaluate(2);
    value_copilot = higher_deg_copilot.evaluate(2);
    cout << "Chat_GPT Test case 20 (Evaluate higher degree polynomial at x=2): " << value_gpt << endl;    // Expected: 49
    cout << "Copilot Test case 20 (Evaluate higher degree polynomial at x=2): " << value_copilot << endl; // Expected: 49

    // Test case 21: Evaluate higher degree polynomial at x=-1
    value_gpt = higher_deg_gpt.evaluate(-1);
    value_copilot = higher_deg_copilot.evaluate(-1);
    cout << "Chat_GPT Test case 21 (Evaluate higher degree polynomial at x=-1): " << value_gpt << endl;    // Expected: 3
    cout << "Copilot Test case 21 (Evaluate higher degree polynomial at x=-1): " << value_copilot << endl; // Expected: 3

    // Test case 22: Adding polynomials where result is a zero polynomial
    vector<double> coeffs_zero_test = {1, -2, 1}; // x^2 - 2x + 1
    PolynomialWithChatGPT poly_zero_test_gpt(coeffs_zero_test);
    PolynomialWithCopilot poly_zero_test_copilot(coeffs_zero_test);
    result_gpt = poly_zero_test_gpt + PolynomialWithChatGPT({-1, 2, -1});
    result_copilot = poly_zero_test_copilot + PolynomialWithCopilot({-1, 2, -1});
    cout << "Chat_GPT Test case 22 (Addition to form zero polynomial): " << result_gpt << endl;    // Expected: 0
    cout << "Copilot Test case 22 (Addition to form zero polynomial): " << result_copilot << endl; // Expected: 0

    // Test case 23: Subtraction resulting in a zero polynomial
    result_gpt = poly_zero_test_gpt - poly_zero_test_gpt;
    result_copilot = poly_zero_test_copilot - poly_zero_test_copilot;
    cout << "Chat_GPT Test case 23 (Subtraction resulting in zero polynomial): " << result_gpt << endl;    // Expected: 0
    cout << "Copilot Test case 23 (Subtraction resulting in zero polynomial): " << result_copilot << endl; // Expected: 0

    // Test case 24: Definite integral of a constant polynomial (e.g., 5) between x=1 and x=3

    definiteIntegral_gpt = constant_gpt.integral(1, 3);
    definiteIntegral_copilot = constant_copilot.integral(1, 3);
    cout << "Chat_GPT Test case 24 (Definite Integral of constant): " << definiteIntegral_gpt << endl;    // Expected: 10
    cout << "Copilot Test case 24 (Definite Integral of constant): " << definiteIntegral_copilot << endl; // Expected: 10

    // Test case 25: Multiplying two higher degree polynomials
    vector<double> coeffs4 = {1, 2, 3}; // 3x^2 + 2x + 1
    vector<double> coeffs5 = {2, 1};    // x + 2
    PolynomialWithChatGPT poly4_gpt(coeffs4);
    PolynomialWithCopilot poly4_copilot(coeffs4);
    PolynomialWithChatGPT poly5_gpt(coeffs5);
    PolynomialWithCopilot poly5_copilot(coeffs5);
    result_gpt = poly4_gpt * poly5_gpt;
    result_copilot = poly4_copilot * poly5_copilot;
    cout << "Chat_GPT Test case 25 (Multiplication of higher degree polynomials): " << result_gpt << endl;    // Expected: 3x^3 + 8x^2 + 5x + 2
    cout << "Copilot Test case 25 (Multiplication of higher degree polynomials): " << result_copilot << endl; // Expected: 3x^3 + 8x^2 + 5x + 2


    // Test case 26: Finding roots for non-trivial polynomials
    PolynomialWithChatGPT cubic_gpt({-6, 11, -6, 1}); // x^3 - 6x^2 + 11x - 6
    PolynomialWithCopilot cubic_copilot({-6, 11, -6, 1});
    root_gpt = cubic_gpt.getRoot(1);                                                  // Finding the root near 1
    root_copilot = cubic_copilot.getRoot(1);                                          // Finding the root near 1
    cout << "Chat_GPT Test case 26 (Root near 1 for cubic): " << root_gpt << endl;    // Expected: Approximation of a root near 1
    cout << "Copilot Test case 26 (Root near 1 for cubic): " << root_copilot << endl; // Expected: Approximation of a root near 1

    // Test case 27: Add negative polynomials
    PolynomialWithChatGPT negPoly_gpt({-1, -2, -3}); // -3x^2 - 2x - 1
    PolynomialWithCopilot negPoly_copilot({-1, -2, -3});
    result_gpt = poly1_gpt + negPoly_gpt;
    result_copilot = poly1_copilot + negPoly_copilot;
    cout << "Chat_GPT Test case 27 (Adding negative polynomials): " << result_gpt << endl;    // Expected: Polynomial subtraction result (diff of coefficients)
    cout << "Copilot Test case 27 (Adding negative polynomials): " << result_copilot << endl; // Expected: Polynomial subtraction result (diff of coefficients)

    // Test case 28: Derivative of a constant polynomial (e.g., 5)
    derivative_gpt = constant_gpt.derivative();
    derivative_copilot = constant_copilot.derivative();
    cout << "Chat_GPT Test case 28 (Derivative of constant polynomial): " << derivative_gpt << endl;    // Expected: 0
    cout << "Copilot Test case 28 (Derivative of constant polynomial): " << derivative_copilot << endl; // Expected: 0

    // Test case 29: Testing equality of two polynomials
    bool isEqual = (poly1_gpt == poly2_gpt);
    cout << "Caht_GPT Test case 29 (Testing equality of two polynomials): " << isEqual << endl;
    isEqual = (poly1_copilot == poly2_copilot);
    cout << "copilot Test case 29 (Testing equality of two polynomials): " << isEqual << endl;

    // Test case 30: Testing equality of a polynomial with itself
    isEqual = (poly1_gpt == poly1_gpt);
    cout << "Caht_GPT Test case 30 (Testing equality of polynomial with itself): " << isEqual << endl;
    isEqual = (poly1_copilot == poly1_copilot);
    cout << "copilot Test case 30 (Testing equality of polynomial with itself): " << isEqual << endl;

    // Test case 31: Setting coefficients of a polynomial
    PolynomialWithChatGPT poly3;
    poly3.setCoefficients({3, 4, 5});
    PolynomialWithCopilot co_poly3;
    co_poly3.setCoefficients({3, 4, 5});
    cout << "Caht_GPT Test case 31 (Setting coefficients of a polynomial): " << poly3 << endl;

    cout << "coplit Test case 31 (Setting coefficients of a polynomial): " << co_poly3 << endl;

    // Test case 32: Addition of two high-degree polynomials
    vector<double> coeffs1_gpt = {1, -0.00001, 100, 0.0001, 0, 0, -500000, 1000000};  // 1000000x^7 - 500000x^6 + 0.0001x^3 + 100x^2 - 0.00001x + 1
    vector<double> coeffs2_gpt = {-2, 0.00002, 50, 0, -0.0002, 0, 400000, -1000000};  // -1000000x^7 + 400000x^6 - 0.0002x^4 + 50x^2 + 0.00002x - 2

    PolynomialWithChatGPT poly11_gpt(coeffs1_gpt);
    PolynomialWithChatGPT poly22_gpt(coeffs2_gpt);

    PolynomialWithCopilot poly11_copilot(coeffs1_gpt);
    PolynomialWithCopilot poly22_copilot(coeffs2_gpt);

    result_gpt = poly11_gpt + poly22_gpt;
    result_copilot = poly11_copilot + poly22_copilot;
    cout << "Chat_GPT Test case 32 (Addition of hard polynomials): " << result_gpt << endl;  // Expected: Polynomial with canceled x^7 term
    cout << "Copilot Test case 32(Addition of hard polynomials): " << result_copilot << endl;

    // Test case 33: Subtraction of two high-degree polynomials
    result_gpt = poly11_gpt - poly22_gpt;
    result_copilot = poly11_copilot - poly22_copilot;
    cout << "Chat_GPT Test case 33 (Subtraction of hard polynomials): " << result_gpt << endl;  // Expected: Polynomial showing differences in coefficients
    cout << "Copilot Test case 33 (Subtraction of hard polynomials): " << result_copilot << endl;

    // Test case 34: Find roots of the high-degree polynomial
    double root11_gpt = poly11_gpt.getRoot(1);  // Trying to find root near 1
    double root11_copilot = poly11_copilot.getRoot(1);
    cout << "Chat_GPT Test case 34 (Root of high-degree poly): " << root11_gpt << endl;
    cout << "Copilot Test case 34 (Root of high-degree poly): " << root11_copilot << endl;


}

// Classes for PolynomialWithChatGPT and PolynomialWithCopilot remain unchanged

void displayMenu() {
    cout << "\n---- Polynomial Operations Menu ----" << endl;
    cout << "1. Add Polynomials" << endl;
    cout << "2. Subtract Polynomials" << endl;
    cout << "3. Multiply Polynomials" << endl;
    cout << "4. Evaluate Polynomial at a Point" << endl;
    cout << "5. Find Derivative" << endl;
    cout << "6. Find Integral (Definite and Indefinite)" << endl;
    cout << "7. Find Root using Newton's Method" << endl;
    cout << "8. Compose Two Polynomials" << endl;
    cout << "9. Run Hardcoded Test Cases" << endl;
    cout << "10. Exit" << endl;
    cout << "Select an option: ";
}

void getPolynomialCoefficients(vector<double>& coeffs) {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;
    coeffs.resize(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        cout << "Coefficient of x^" << i << ": ";
        cin >> coeffs[i];
    }
}
int main() {
    int choice;
    vector<double> coeffs1, coeffs2;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 10) {
            cout << "Exiting..." << endl;
            break;
        }

        switch (choice) {
            case 1: {
                cout << "\nEnter coefficients for the first polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);
                cout << "\nEnter coefficients for the second polynomial:" << endl;
                getPolynomialCoefficients(coeffs2);

                PolynomialWithChatGPT poly1ChatGPT(coeffs1), poly2ChatGPT(coeffs2);
                PolynomialWithCopilot poly1Copilot(coeffs1), poly2Copilot(coeffs2);

                cout << "\nResult of addition:" << endl;
                cout << "ChatGPT: " << (poly1ChatGPT + poly2ChatGPT) << endl;
                cout << "Copilot: " << (poly1Copilot + poly2Copilot) << endl;
                break;
            }
            case 2: {
                cout << "\nEnter coefficients for the first polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);
                cout << "\nEnter coefficients for the second polynomial:" << endl;
                getPolynomialCoefficients(coeffs2);

                PolynomialWithChatGPT poly1ChatGPT(coeffs1), poly2ChatGPT(coeffs2);
                PolynomialWithCopilot poly1Copilot(coeffs1), poly2Copilot(coeffs2);

                cout << "\nResult of subtraction:" << endl;
                cout << "ChatGPT: " << (poly1ChatGPT - poly2ChatGPT) << endl;
                cout << "Copilot: " << (poly1Copilot - poly2Copilot) << endl;
                break;
            }
            case 3: {
                cout << "\nEnter coefficients for the first polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);
                cout << "\nEnter coefficients for the second polynomial:" << endl;
                getPolynomialCoefficients(coeffs2);

                PolynomialWithChatGPT poly1ChatGPT(coeffs1), poly2ChatGPT(coeffs2);
                PolynomialWithCopilot poly1Copilot(coeffs1), poly2Copilot(coeffs2);

                cout << "\nResult of multiplication:" << endl;
                cout << "ChatGPT: " << (poly1ChatGPT * poly2ChatGPT) << endl;
                cout << "Copilot: " << (poly1Copilot * poly2Copilot) << endl;
                break;
            }
            case 4: {
                cout << "\nEnter coefficients for the polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);

                double x;
                cout << "Enter the value of x: ";
                cin >> x;

                PolynomialWithChatGPT polyChatGPT(coeffs1);
                PolynomialWithCopilot polyCopilot(coeffs1);

                cout << "Polynomial evaluated at x = " << x << " is:" << endl;
                cout << "ChatGPT: " << polyChatGPT.evaluate(x) << endl;
                cout << "Copilot: " << polyCopilot.evaluate(x) << endl;
                break;
            }
            case 5: {
                cout << "\nEnter coefficients for the polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);

                PolynomialWithChatGPT polyChatGPT(coeffs1);
                PolynomialWithCopilot polyCopilot(coeffs1);

                cout << "Derivative of the polynomial:" << endl;
                cout << "ChatGPT: " << polyChatGPT.derivative() << endl;
                cout << "Copilot: " << polyCopilot.derivative() << endl;
                break;
            }
            case 6: {
                cout << "\nEnter coefficients for the polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);

                PolynomialWithChatGPT polyChatGPT(coeffs1);
                PolynomialWithCopilot polyCopilot(coeffs1);

                cout << "Indefinite integral of the polynomial:" << endl;
                cout << "ChatGPT: " << polyChatGPT.integral() << endl;
                cout << "Copilot: " << polyCopilot.integral() << endl;

                double x1, x2;
                cout << "Enter lower limit for definite integral: ";
                cin >> x1;
                cout << "Enter upper limit for definite integral: ";
                cin >> x2;

                cout << "Definite integral from " << x1 << " to " << x2 << " is:" << endl;
                cout << "ChatGPT: " << polyChatGPT.integral(x1, x2) << endl;
                cout << "Copilot: " << polyCopilot.integral(x1, x2) << endl;
                break;
            }
            case 7: {
                cout << "\nEnter coefficients for the polynomial:" << endl;
                getPolynomialCoefficients(coeffs1);

                PolynomialWithChatGPT polyChatGPT(coeffs1);
                PolynomialWithCopilot polyCopilot(coeffs1);

                double guess;
                cout << "Enter initial guess for root: ";
                cin >> guess;

                try {
                    cout << "Root of the polynomial:" << endl;
                    cout << "ChatGPT: " << polyChatGPT.getRoot(guess) << endl;
                    cout << "Copilot: " << polyCopilot.getRoot(guess) << endl;
                } catch (const exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 8: {
                cout << "\nEnter coefficients for the first polynomial (p):" << endl;
                getPolynomialCoefficients(coeffs1);
                cout << "\nEnter coefficients for the second polynomial (q):" << endl;
                getPolynomialCoefficients(coeffs2);

                PolynomialWithChatGPT pChatGPT(coeffs1), qChatGPT(coeffs2);
                PolynomialWithCopilot pCopilot(coeffs1), qCopilot(coeffs2);

                cout << "\nResult of composition p(q(x)):" << endl;
                cout << "ChatGPT: " << pChatGPT.compose(qChatGPT) << endl;
                cout << "Copilot: " << pCopilot.compose(qCopilot) << endl;
                break;
            }
            case 9: {
                runHardCodedTestCases();
                break;
            }
        }
    }
}



