#pragma once

#include <iostream>

class BigNumber;
// store exponent handling separately since there are so many operations to
// overload
class Exponent {
 public:
  Exponent(int i);
  Exponent(const BigNumber& bn);

  Exponent(const Exponent& other);
  Exponent& operator=(const Exponent& other);
  ~Exponent();

  friend std::ostream& operator<<(std::ostream& os, const Exponent& e);

  friend Exponent operator+(Exponent a, Exponent b);
  friend Exponent operator-(Exponent a, Exponent b);
  friend Exponent operator*(Exponent a, Exponent b);
  friend Exponent operator/(Exponent a, Exponent b);
  friend bool operator==(Exponent a, Exponent b);
  friend bool operator!=(Exponent a, Exponent b);
  friend bool operator<(Exponent a, Exponent b);
  friend bool operator>(Exponent a, Exponent b);
  friend bool operator<=(Exponent a, Exponent b);
  friend bool operator>=(Exponent a, Exponent b);
  Exponent operator-();
  Exponent& operator+=(Exponent n);
  Exponent& operator-=(Exponent n);
  Exponent& operator*=(Exponent n);
  Exponent& operator/=(Exponent n);
  Exponent& operator++();
  Exponent& operator--();
  Exponent operator++(int);
  Exponent operator--(int);

  BigNumber asBigNum() const;
  double asDouble() const;

 private:
  // could probably use a union
  int i = 0;
  BigNumber* bn = nullptr;

  void copy(const Exponent& other);
  void destroy();

  // checks if needs to change to BigNumber
  void checkMagnitude();
};
