#include "Complex.h"
#include <cmath>

Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }


Complex& Complex::operator+=(const Complex& rhs) {
    this->real += rhs.real;
    this->imag += rhs.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) {
    this->real -= rhs.real;
    this->imag -= rhs.imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) {
    double oldReal = this->real;
    this->real = (oldReal * rhs.real) - (this->imag * rhs.imag);
    this->imag = (oldReal * rhs.imag) + (this->imag * rhs.real);
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    double denominator = (rhs.real * rhs.real) + (rhs.imag * rhs.imag);
    double oldReal = this->real;
    this->real = (oldReal * rhs.real + this->imag * rhs.imag) / denominator;
    this->imag = (this->imag * rhs.real - oldReal * rhs.imag) / denominator;
    return *this;
}

Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs;
    return lhs;
}

Complex operator-(Complex lhs, const Complex& rhs) {
    lhs -= rhs;
    return lhs;
}

Complex operator*(Complex lhs, const Complex& rhs) {
    lhs *= rhs;
    return lhs;
}

Complex operator/(Complex lhs, const Complex& rhs) {
    lhs /= rhs;
    return lhs;
}

Complex& Complex::operator++() {
    this->real += 1.0;
    return *this;
}

Complex Complex::operator++(int) {
    Complex temp = *this;
    ++(*this);
    return temp;
}

Complex& Complex::operator--() {
    this->real -= 1.0;
    return *this;
}

Complex Complex::operator--(int) {
    Complex temp = *this;
    --(*this);
    return temp;
}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

bool Complex::operator!() const {
    return (real == 0.0 && imag == 0.0);
}

double& Complex::operator[](int index) {
    if (index == 0) return real;
    if (index == 1) return imag;
    throw std::out_of_range("Index must be 0 (real) or 1 (imag)");
}

const double& Complex::operator[](int index) const {
    if (index == 0) return real;
    if (index == 1) return imag;
    throw std::out_of_range("Index must be 0 (real) or 1 (imag)");
}

double Complex::operator()() const {
    return std::sqrt(real*real + imag*imag);
}

std::ostream& operator<<(std::ostream& os, const Complex& obj) {
    os << "(" << obj.real << (obj.imag >= 0 ? "+" : "") << obj.imag << "i)";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& obj) {
    is >> obj.real >> obj.imag;
    return is;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return lhs.real == rhs.real && lhs.imag == rhs.imag;
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Complex& lhs, const Complex& rhs) {
    if (lhs.real != rhs.real) {
        return lhs.real < rhs.real;
    }
    return lhs.imag < rhs.imag;
}

bool operator>(const Complex& lhs, const Complex& rhs) {
    return rhs < lhs;
}

bool operator<=(const Complex& lhs, const Complex& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Complex& lhs, const Complex& rhs) {
    return !(lhs < rhs);
}