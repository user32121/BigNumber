#pragma once

#include <iostream>

#include "Exponent.h"

class Exponent;
// my attempt at implementing a big number
class BigNumber {
 public:
  double mantissa;
  Exponent exponent;

  BigNumber(double f);
  BigNumber(double mantissa, Exponent exponent);

  friend std::ostream& operator<<(std::ostream& os, const BigNumber& n);

  friend BigNumber operator+(BigNumber a, BigNumber b);
  friend BigNumber operator-(BigNumber a, BigNumber b);
  friend BigNumber operator*(BigNumber a, BigNumber b);
  friend BigNumber operator/(BigNumber a, BigNumber b);
  friend bool operator==(BigNumber a, BigNumber b);
  friend bool operator!=(BigNumber a, BigNumber b);
  friend bool operator<(BigNumber a, BigNumber b);
  friend bool operator>(BigNumber a, BigNumber b);
  friend bool operator<=(BigNumber a, BigNumber b);
  friend bool operator>=(BigNumber a, BigNumber b);
  BigNumber operator-();
  BigNumber& operator+=(BigNumber n);
  BigNumber& operator-=(BigNumber n);
  BigNumber& operator*=(BigNumber n);
  BigNumber& operator/=(BigNumber n);
  BigNumber& operator++();
  BigNumber& operator--();
  BigNumber operator++(int);
  BigNumber operator--(int);

  friend BigNumber pow(BigNumber a, BigNumber b);

  double asDouble() const;

 private:
  // shift so that magnitude of mantissa is in the range [1,10)
  void normalize();
  // shift so that exponent matches target
  void shift(const Exponent& target);
};
