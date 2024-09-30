/*header file for fraction class
    * fraction_21mh124.h
    * Created on: Sep 30, 2024
    * Author: Michael Han
*/

#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

// Exception class to handle Fraction-related errors
class FractionException {
public:
    // Constructor to initialize the error message and function to retrieve the error message
    FractionException(const string& message) : message(message) {}
    
    const string& what() const { return message; }

private:
    string message;
};

class Fraction {
    private:
        int greatestCommonDivisor(int a, int b) const;
        int numer;
        int denom;

    public:
        Fraction();
        Fraction(int);
        Fraction(int, int);
        int numerator() const { return numer; }
        int denominator() const { return denom; }

        //Overloaded operators
        bool operator ==(const Fraction&) const;
        bool operator <=(const Fraction&) const;
        bool operator >=(const Fraction&) const;

        Fraction operator -() const;
        Fraction operator ++(int);
        Fraction& operator ++();
        Fraction& operator +=(const Fraction&);

        //Friend functions
        friend bool operator <(const Fraction&, const Fraction&);
        friend bool operator >(const Fraction&, const Fraction&);
        friend Fraction operator +(const Fraction&, const Fraction&);
        friend Fraction operator -(const Fraction&, const Fraction&);
        friend Fraction operator /(const Fraction&, const Fraction&);
        friend Fraction operator *(const Fraction&, const Fraction&);
        friend bool operator !=(const Fraction&, const Fraction&);

        //Stream insertion and extraction
        friend ostream& operator <<(ostream&, const Fraction&);
        friend istream& operator >>(istream&, Fraction&);
};

inline int Fraction::greatestCommonDivisor(int a, int d) const{
    if (d == 0) {
        return a;
    } 
    return greatestCommonDivisor(d, a % d);
    
};
