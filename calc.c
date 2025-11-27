#include "calc.h"
// Custom math functions without using math.h

// Basic operations
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return b != 0 ? a / b : 0; }

// Power using fast exponentiation
double power(double a, double b) {
    if (b == 0) return 1;
    if (b < 0) return 1 / power(a, -b);
    double result = 1;
    for (int i = 0; i < (int)b; i++) result *= a;
    return result;
}

// Factorial
double factorial(double n) {
    if (n < 0) return 0;
    double res = 1;
    for (int i = 1; i <= (int)n; i++) res *= i;
    return res;
}

// Taylor series for sine
double sine(double x) {
    double term = x;
    double sum = x;
    for (int i = 1; i <= 10; i++) {
        term *= -1 * x * x / (2 * i * (2 * i + 1));
        sum += term;
    }
    return sum;
}

// Taylor series for cosine
double cosine(double x) {
    double term = 1;
    double sum = 1;
    for (int i = 1; i <= 10; i++) {
        term *= -1 * x * x / (2 * i * (2 * i - 1));
        sum += term;
    }
    return sum;
}

// Tangent using sin/cos
double tangent(double x) {
    double c = cosine(x);
    return c == 0 ? 0 : sine(x) / c;
}

// Natural logarithm using Newton's method
double ln(double x) {
    if (x <= 0) return 0;
    double y = x;
    for (int i = 0; i < 20; i++) {
        y = y - (power(2.718281828, y) - x) / power(2.718281828, y);
    }
    return y;
}

// Log base 10
double logarithm(double x) {
    return x > 0 ? ln(x) / 2.302585093 : 0;
}

// Square root using Newton's method
double square_root(double x) {
    if (x < 0) return 0;
    double guess = x;
    for (int i = 0; i < 20; i++) guess = 0.5 * (guess + x / guess);
    return guess;
}

// Exponential function using Taylor series
double exp_value(double x) {
    double term = 1;
    double sum = 1;
    for (int i = 1; i <= 20; i++) {
        term *= x / i;
        sum += term;
    }
    return sum;
}
