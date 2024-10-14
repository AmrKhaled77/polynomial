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
    // Implement composition using Horner's method
         PolynomialWIthGemini result(degree() + q.degree());
           for (int i = coeffs.size() - 1; i >= 0; --i) {
              double temp = coeffs[i];
          for (int j = q.degree() - 2; j >= 0; --j) {
              temp = temp * q.coeffs[j] + result[i + j + 1];
           }
          result[i] = temp;
        }
            return result;
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
  // Additional method to create a polynomial from user input
    static PolynomialWIthGemini createFromInput() {
        cout << "Enter the coefficients of the polynomial (separated by spaces): ";
        vector<double> coefficients;
        double coeff;
        while (cin >> coeff) {
            coefficients.push_back(coeff);
        }
        cin.clear(); // Clear any errors from reading coefficients
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input on line
        return PolynomialWIthGemini(coefficients);
    }
};
int main() {
    PolynomialWIthGemini p1, p2;
    int choice;

    do {
        cout << "\nPolynomial Operations Menu:\n";
        cout << "1. Create Polynomial 1 (from input)\n";
        cout << "2. Create Polynomial 2 (from input)\n";
        cout << "3. Add Polynomials\n";
        cout << "4. Subtract Polynomials\n";
        cout << "5. Multiply Polynomials\n";
        cout << "6. Evaluate Polynomial 1\n";
        cout << "7. Evaluate Polynomial 2\n";
        cout << "8. Compose Polynomials\n";
        cout << "9. Differentiate Polynomial 1\n";
        cout << "10. Differentiate Polynomial 2\n";
        cout << "11. Integrate Polynomial 1\n";
        cout << "12. Integrate Polynomial 2\n";
        cout << "13. Find Root of Polynomial 1\n";
        cout << "14. Find Root of Polynomial 2\n";
        cout << "15. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                p1 = PolynomialWIthGemini::createFromInput();
                break;
            case 2:
                p2 = PolynomialWIthGemini::createFromInput();
                break;
            case 3:
                p1 = p1 + p2;
                cout << "Result: " << p1 << endl;
                break;
            case 4:
                p1 = p1 - p2;
                cout << "Result: " << p1 << endl;
                break;
            case 5:
                p1 = p1 * p2;
                cout << "Result: " << p1 << endl;
                break;
            case 6:
                cout << "Enter x-value: ";
                double x;
                cin >> x;
                cout << "Evaluation: " << p1.evaluate(x) << endl;
                break;
            case 7:
                cout << "Enter x-value: ";
                cin >> x;
                cout << "Evaluation: " << p2.evaluate(x) << endl;
                break;
            case 8:
                p1 = p1.compose(p2);
                cout << "Result: " << p1 << endl;
                break;
            case 9:
                p1 = p1.derivative();
                cout << "Derivative: " << p1 << endl;
                break;
            case 10:
                p2 = p2.derivative();
                cout << "Derivative: " << p2 << endl;
                break;
            case 11:
                p1 = p1.integral();
                cout << "Integral: " << p1 << endl;
                break;
            case 12:
                p2 = p2.integral();
                cout << "Integral: " << p2 << endl;
                break;
            case 13:
                cout << "Enter initial guess: ";
                cin >> x;
                try {
                    double root = p1.getRoot(x);
                    cout << "Root: " << root << endl;
                } catch (const runtime_error& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            case 14:
                cout << "Enter initial guess: ";
                cin >> x;
                try {
                    double root = p2.getRoot(x);
                    cout << "Root: " << root << endl;
                } catch (const runtime_error& e) {
                    cerr << "Error: " << e.what() << endl;
                }
                break;
            case 15:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 15);

    return 0;
}
