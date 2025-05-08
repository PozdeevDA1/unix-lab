#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double power(double base, int exponent) {
    if (exponent == 0) {
        if (base == 0) {
            throw runtime_error("0^0 is undefined.");
        }
        return 1;
    }
    if (base == 0 && exponent < 0) {
        throw runtime_error("Division by zero (0 raised to a negative power).");
    }
    bool negative = exponent < 0;
    exponent = abs(exponent);
    
    double result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return negative ? 1.0 / result : result;
}

int main() {
    double a, b;
    char op; // Используем char вместо string
    
    cout << "Enter first number: ";
    cin >> a;
    
    cout << "Enter operator (+/-/^): ";
    cin >> op;
    
    cout << "Enter second number: ";
    cin >> b;
    
    try {
        if (op == '+') {
            cout << "Result: " << a + b << endl;
        } else if (op == '-') {
            cout << "Result: " << a - b << endl;
        } else if (op == '^') {
            if (floor(b) != b) {
                throw runtime_error("Exponent must be an integer.");
            }
            int exponent = static_cast<int>(b);
            cout << "Result: " << power(a, exponent) << endl;
        } else {
            throw runtime_error("Invalid operator. Use +, -, or ^.");
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}