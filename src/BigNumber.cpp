#include "BigNumber.h"

#include <math.h>

BigNumber::BigNumber(double f) : BigNumber{f, 0} {}

BigNumber::BigNumber(double mantissa, Exponent exponent)
    : mantissa{mantissa}, exponent{exponent} {
  normalize();
}

BigNumber BigNumber::operator-() { return BigNumber{-mantissa, exponent}; }

BigNumber& BigNumber::operator+=(BigNumber n) {
  if (n.exponent > exponent) {
    std::swap(*this, n);
  }
  n.shift(exponent);
  mantissa += n.mantissa;
  normalize();
  return *this;
}

BigNumber& BigNumber::operator-=(BigNumber n) { return (*this) += -n; }

BigNumber& BigNumber::operator*=(BigNumber n) {
  mantissa *= n.mantissa;
  exponent += n.exponent;
  normalize();
  return *this;
}

BigNumber& BigNumber::operator/=(BigNumber n) {
  mantissa /= n.mantissa;
  exponent -= n.exponent;
  normalize();
  return *this;
}

BigNumber& BigNumber::operator++() {
  *this += 1;
  return *this;
}

BigNumber& BigNumber::operator--() {
  *this -= 1;
  return *this;
}

BigNumber BigNumber::operator++(int) {
  BigNumber copy = *this;
  ++*this;
  return copy;
}

BigNumber BigNumber::operator--(int) {
  BigNumber copy = *this;
  --*this;
  return copy;
}

double BigNumber::asDouble() const {
  BigNumber copy = *this;
  copy.shift(0);
  return copy.mantissa;
}

void BigNumber::normalize() {
  if (!isnormal(mantissa)) {
    return;
  }
  int delta = int(floor(log10(abs(mantissa))));
  exponent += delta;
  mantissa /= pow(10, delta);
}

void BigNumber::shift(const Exponent& target) {
  mantissa *= pow(10, (exponent - target).asDouble());
  exponent = target;
}

std::ostream& operator<<(std::ostream& os, const BigNumber& n) {
  os << n.mantissa;
  if (!isnormal(n.mantissa)) {
    return os;
  }
  os << 'e' << n.exponent;
  return os;
}

BigNumber operator+(BigNumber a, BigNumber b) {
  if (b.exponent > a.exponent) {
    std::swap(a, b);
  }
  b.shift(a.exponent);
  return BigNumber{a.mantissa + b.mantissa, a.exponent};
}

BigNumber operator-(BigNumber a, BigNumber b) { return a + -b; }

BigNumber operator*(BigNumber a, BigNumber b) {
  return BigNumber{a.mantissa * b.mantissa, a.exponent + b.exponent};
}

BigNumber operator/(BigNumber a, BigNumber b) {
  return BigNumber{a.mantissa / b.mantissa, a.exponent - b.exponent};
}

bool operator==(BigNumber a, BigNumber b) {
  return a.mantissa == b.mantissa && a.exponent == b.exponent;
}

bool operator!=(BigNumber a, BigNumber b) { return !(a == b); }

bool operator<(BigNumber a, BigNumber b) {
  if (a.exponent == b.exponent) {
    return a.mantissa < b.mantissa;
  } else {
    return a.exponent < b.exponent;
  }
}

bool operator>(BigNumber a, BigNumber b) { return b < a; }

bool operator<=(BigNumber a, BigNumber b) { return a < b || a == b; }

bool operator>=(BigNumber a, BigNumber b) { return a > b || a == b; }

BigNumber pow(BigNumber a, BigNumber b) {
  BigNumber logRes = b * (log10(a.mantissa) + a.exponent.asBigNum());
  BigNumber logRes2 = logRes;
  logRes2.shift(0);
  if (std::isnormal(logRes2.mantissa)) {
    return BigNumber{pow(10, fmod(logRes2.mantissa, 1)),
                     BigNumber{floor(logRes2.mantissa)}};
  } else {
    return BigNumber{1, logRes};
  }
}
