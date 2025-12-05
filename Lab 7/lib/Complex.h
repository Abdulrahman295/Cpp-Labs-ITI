#pragma once

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0);

    double getReal() const;
    double getImag() const;

    // Compound Assignment
    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);

    // Unary Operators
    Complex& operator++();
    Complex operator++(int);
    Complex& operator--();
    Complex operator--(int);
    Complex operator-() const;
    bool operator!() const;

    // Data Access Operator
    double& operator[](int index);
    const double& operator[](int index) const;

    // Function Call Operator
    double operator()() const;

    // Binary Arithmetic Operators
    friend Complex operator+(Complex lhs, const Complex& rhs);
    friend Complex operator-(Complex lhs, const Complex& rhs);
    friend Complex operator*(Complex lhs, const Complex& rhs);
    friend Complex operator/(Complex lhs, const Complex& rhs);

    // Stream Input/Output Operators
    friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
    friend std::istream& operator>>(std::istream& is, Complex& obj);

    // Comparison Operators
    friend bool operator==(const Complex& lhs, const Complex& rhs);
    friend bool operator!=(const Complex& lhs, const Complex& rhs);
    friend bool operator<(const Complex& lhs, const Complex& rhs);
    friend bool operator>(const Complex& lhs, const Complex& rhs);
    friend bool operator<=(const Complex& lhs, const Complex& rhs);
    friend bool operator>=(const Complex& lhs, const Complex& rhs);
};