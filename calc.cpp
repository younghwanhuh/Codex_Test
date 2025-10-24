#include "calc.h"

#include <cmath>
#include <stdexcept>

double Calculator::add(double lhs, double rhs) const {
    return lhs + rhs;
}

double Calculator::subtract(double lhs, double rhs) const {
    return lhs - rhs;
}

double Calculator::multiply(double lhs, double rhs) const {
    return lhs * rhs;
}

double Calculator::divide(double lhs, double rhs) const {
    if (rhs == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return lhs / rhs;
}

long long Calculator::modulo(long long lhs, long long rhs) const {
    if (rhs == 0) {
        throw std::invalid_argument("Modulo by zero");
    }
    return lhs % rhs;
}

double Calculator::power(double base, double exponent) const {
    return std::pow(base, exponent);
}

double Calculator::square_root(double value) const {
    if (value < 0.0) {
        throw std::invalid_argument("Square root of negative number");
    }
    return std::sqrt(value);
}
