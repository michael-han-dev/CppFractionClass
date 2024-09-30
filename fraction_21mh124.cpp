#include "fraction_21mh124.h"
#include <iostream>
#include <cmath>  // for std::abs
#include <stdexcept>

using namespace std;

// Default constructor: initializes fraction to 0/1
Fraction::Fraction() : numer(0), denom(1) {}

// Constructor for whole number: n -> n/1
Fraction::Fraction(int numerator) : numer(numerator), denom(1) {}

// Constructor for fraction with two integers: n/d
Fraction::Fraction(int numerator, int denominator) : numer(numerator), denom(denominator) {
    if (denominator == 0) {
        throw FractionException("Denominator cannot be zero");
    }

    int gcd = greatestCommonDivisor(abs(numerator), abs(denominator));
    numer /= gcd;
    denom /= gcd;

    // Ensure the denominator is always positive
    if (denom < 0) {
        numer = -numer;
        denom = -denom;
    }
}

// Unary negation operator
Fraction Fraction::operator -() const {
    return Fraction(-numer, denom);
}

// Post-increment operator: Fraction++
Fraction Fraction::operator ++(int) {
    Fraction temp = *this;
    numer += denom;  // Add 1 (numer += denom) to the fraction
    return temp;
}

// Pre-increment operator: ++Fraction
Fraction& Fraction::operator ++() {
    numer += denom;
    return *this;
}

// Addition assignment operator: Fraction += Fraction
Fraction& Fraction::operator +=(const Fraction& other) {
    numer = numer * other.denom + other.numer * denom;
    denom = denom * other.denom;

    int gcd = greatestCommonDivisor(abs(numer), abs(denom));
    numer /= gcd;
    denom /= gcd;

    return *this;
}

// Comparison operators

// Equality operator: Fraction == Fraction
bool Fraction::operator ==(const Fraction& other) const {
    return numer == other.numer && denom == other.denom;
}

// Less than or equal to operator: Fraction <= Fraction
bool Fraction::operator <=(const Fraction& other) const {
    return numer * other.denom <= other.numer * denom;
}

// Greater than or equal to operator: Fraction >= Fraction
bool Fraction::operator >=(const Fraction& other) const {
    return numer * other.denom >= other.numer * denom;
}

// Less than operator: Fraction < Fraction
bool operator <(const Fraction& lhs, const Fraction& rhs) {
    return lhs.numer * rhs.denom < rhs.numer * lhs.denom;
}

// Greater than operator: Fraction > Fraction
bool operator >(const Fraction& lhs, const Fraction& rhs) {
    return lhs.numer * rhs.denom > rhs.numer * lhs.denom;
}

// Addition operator: Fraction + Fraction
Fraction operator +(const Fraction& lhs, const Fraction& rhs) {
    int numer = lhs.numer * rhs.denom + rhs.numer * lhs.denom;
    int denom = lhs.denom * rhs.denom;
    return Fraction(numer, denom);
}

// Subtraction operator: Fraction - Fraction
Fraction operator -(const Fraction& lhs, const Fraction& rhs) {
    int numer = lhs.numer * rhs.denom - rhs.numer * lhs.denom;
    int denom = lhs.denom * rhs.denom;
    return Fraction(numer, denom);
}

// Multiplication operator: Fraction * Fraction
Fraction operator *(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numer * rhs.numer, lhs.denom * rhs.denom);
}

// Division operator: Fraction / Fraction
Fraction operator /(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.numer == 0) {
        throw FractionException("Cannot divide by zero");
    }
    return Fraction(lhs.numer * rhs.denom, lhs.denom * rhs.numer);
}

// Inequality operator: Fraction != Fraction
bool operator !=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs == rhs);
}

// Stream insertion operator: << (for output)
ostream& operator <<(ostream& os, const Fraction& fraction) {
    os << fraction.numer << "/" << fraction.denom;
    return os;
}

// Stream extraction operator: >> (for input)
istream& operator >>(istream& is, Fraction& fraction) {
    int num = 0;
    int denom = 1;
    char slash;

    is >> num;
    if (is.peek() == '/') {
        is >> slash >> denom;
    }

    if (denom == 0) {
        throw FractionException("Denominator cannot be zero");
    }

    fraction = Fraction(num, denom);
    return is;
}
