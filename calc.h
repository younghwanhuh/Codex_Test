#ifndef CALC_H
#define CALC_H

class Calculator {
public:
    double add(double lhs, double rhs) const;
    double subtract(double lhs, double rhs) const;
    double multiply(double lhs, double rhs) const;
    double divide(double lhs, double rhs) const;
    long long modulo(long long lhs, long long rhs) const;
    double power(double base, double exponent) const;
    double square_root(double value) const;
};

#endif  // CALC_H
