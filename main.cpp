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

void printMenu() {
    cout << "\n=== Polynomial Menu ===\n";
    cout << "1. Create polynomial\n";
    cout << "2. Add two polynomials\n";
    cout << "3. Subtract two polynomials\n";
    cout << "4. Multiply two polynomials\n";
    cout << "5. Evaluate polynomial\n";
    cout << "6. Find root (using Newton's method)\n";
    cout << "7. Derivative of polynomial\n";
    cout << "8. Indefinite integral of polynomial\n";
    cout << "9. Definite integral between two points\n";
    cout << "0. Exit\n";
    cout << "Select an option: ";
}

PolynomialWithChatGPT inputPolynomial() {
    int degree;
    cout << "Enter the degree of the polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1);
    cout << "Enter the coefficients (from constant term to highest degree term):\n";
    for (int i = 0; i <= degree; i++) {
        cout << "Coefficient of x^" << i << ": ";
        cin >> coeffs[i];
    }

    return PolynomialWithChatGPT(coeffs);
}






int main() {
    PolynomialWithChatGPT poly1, poly2, result;
    int choice;
    bool running = true;

    while (running) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                // Create polynomial
                poly1 = inputPolynomial();
                cout << "Polynomial created: " << poly1 << endl;
                break;
            }
            case 2: {
                // Add two polynomials
                cout << "Enter first polynomial:\n";
                poly1 = inputPolynomial();
                cout << "Enter second polynomial:\n";
                poly2 = inputPolynomial();
                result = poly1 + poly2;
                cout << "Result of addition: " << result << endl;
                break;
            }
            case 3: {
                // Subtract two polynomials
                cout << "Enter first polynomial:\n";
                poly1 = inputPolynomial();
                cout << "Enter second polynomial:\n";
                poly2 = inputPolynomial();
                result = poly1 - poly2;
                cout << "Result of subtraction: " << result << endl;
                break;
            }
            case 4: {
                // Multiply two polynomials
                cout << "Enter first polynomial:\n";
                poly1 = inputPolynomial();
                cout << "Enter second polynomial:\n";
                poly2 = inputPolynomial();
                result = poly1 * poly2;
                cout << "Result of multiplication: " << result << endl;
                break;
            }
            case 5: {
                // Evaluate polynomial
                cout << "Enter polynomial:\n";
                poly1 = inputPolynomial();
                double x;
                cout << "Enter value of x: ";
                cin >> x;
                cout << "Result of evaluation at x = " << x << ": " << poly1.evaluate(x) << endl;
                break;
            }
            case 6: {
                // Find root using Newton's method
                cout << "Enter polynomial:\n";
                poly1 = inputPolynomial();
                double guess;
                cout << "Enter initial guess for the root: ";
                cin >> guess;
                double root = poly1.getRoot(guess);
                cout << "Root found: " << root << endl;
                break;
            }
            case 7: {
                // Derivative of polynomial
                cout << "Enter polynomial:\n";
                poly1 = inputPolynomial();
                result = poly1.derivative();
                cout << "Derivative of the polynomial: " << result << endl;
                break;
            }
            case 8: {
                // Indefinite integral of polynomial
                cout << "Enter polynomial:\n";
                poly1 = inputPolynomial();
                result = poly1.integral();
                cout << "Indefinite integral of the polynomial: " << result << " + C" << endl;
                break;
            }
            case 9: {
                // Definite integral between two points
                cout << "Enter polynomial:\n";
                poly1 = inputPolynomial();
                double x1, x2;
                cout << "Enter lower limit x1: ";
                cin >> x1;
                cout << "Enter upper limit x2: ";
                cin >> x2;
                double integralResult = poly1.integral(x1, x2);
                cout << "Definite integral between x1 = " << x1 << " and x2 = " << x2 << ": " << integralResult << endl;
                break;
            }
            case 0: {
                // Exit
                running = false;
                cout << "Exiting program.\n";
                break;
            }
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
