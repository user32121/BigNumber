#include "Exponent.h"

#include "BigNumber.h"

Exponent::Exponent(int i) : i{i} {}

Exponent::Exponent(const BigNumber& bn) : bn{new BigNumber{bn}} {}

Exponent::Exponent(const Exponent& other) { copy(other); }

Exponent& Exponent::operator=(const Exponent& other) {
  destroy();
  copy(other);
  return *this;
}

Exponent::~Exponent() { destroy(); }

Exponent Exponent::operator-() {
  if (bn == nullptr) {
    return Exponent{-i};
  } else {
    return Exponent{-*bn};
  }
}

Exponent& Exponent::operator+=(Exponent n) {
  if (n.bn == nullptr) {
    if (bn == nullptr) {
      i += n.i;
    } else {
      *bn += n.i;
    }
  } else {
    if (bn == nullptr) {
      bn = new BigNumber(i);
    }
    *bn += *n.bn;
  }
  checkMagnitude();
  return *this;
}

Exponent& Exponent::operator-=(Exponent n) { return (*this) += -n; }

Exponent& Exponent::operator*=(Exponent n) {
  if (n.bn == nullptr) {
    if (bn == nullptr) {
      i *= n.i;
    } else {
      *bn *= n.i;
    }
  } else {
    if (bn == nullptr) {
      bn = new BigNumber(i);
    }
    *bn *= *n.bn;
  }
  checkMagnitude();
  return *this;
}

Exponent& Exponent::operator/=(Exponent n) {
  if (n.bn == nullptr) {
    if (bn == nullptr) {
      i /= n.i;
    } else {
      *bn /= n.i;
    }
  } else {
    if (bn == nullptr) {
      bn = new BigNumber(i);
    }
    *bn /= *n.bn;
  }
  checkMagnitude();
  return *this;
}

Exponent& Exponent::operator++() {
  if (bn == nullptr) {
    ++i;
  } else {
    ++*bn;
  }
  checkMagnitude();
  return *this;
}

Exponent& Exponent::operator--() {
  if (bn == nullptr) {
    --i;
  } else {
    --*bn;
  }
  checkMagnitude();
  return *this;
}

Exponent Exponent::operator++(int) {
  Exponent copy = *this;
  ++*this;
  return copy;
}

Exponent Exponent::operator--(int) {
  Exponent copy = *this;
  --*this;
  return copy;
}

BigNumber Exponent::asBigNum() const {
  if (bn == nullptr) {
    return i;
  } else {
    return *bn;
  }
}

double Exponent::asDouble() const {
  if (bn == nullptr) {
    return i;
  } else {
    return bn->asDouble();
  }
}

void Exponent::copy(const Exponent& other) {
  i = other.i;
  if (other.bn != nullptr) {
    bn = new BigNumber{*other.bn};
  }
}

void Exponent::destroy() {
  delete bn;
  bn = nullptr;
}

void Exponent::checkMagnitude() {
  if (bn == nullptr && abs(i) >= 1000) {
    bn = new BigNumber(i);
  }
}

std::ostream& operator<<(std::ostream& os, const Exponent& e) {
  if (e.bn == nullptr) {
    os << e.i;
  } else {
    os << *e.bn;
  }
  return os;
}

Exponent operator+(Exponent a, Exponent b) {
  Exponent copy = a;
  copy += b;
  return copy;
}

Exponent operator-(Exponent a, Exponent b) { return a + -b; }

Exponent operator*(Exponent a, Exponent b) {
  Exponent copy = a;
  copy *= b;
  return copy;
}

Exponent operator/(Exponent a, Exponent b) {
  Exponent copy = a;
  copy /= b;
  return copy;
}

bool operator==(Exponent a, Exponent b) {
  if (a.bn == nullptr && b.bn == nullptr) {
    return a.i == b.i;
  } else {
    BigNumber abn = a.i;
    BigNumber bbn = b.i;
    if (a.bn != nullptr) {
      abn = *a.bn;
    }
    if (b.bn != nullptr) {
      bbn = *b.bn;
    }
    return abn == bbn;
  }
}

bool operator!=(Exponent a, Exponent b) { return !(a == b); }

bool operator<(Exponent a, Exponent b) {
  if (a.bn == nullptr && b.bn == nullptr) {
    return a.i < b.i;
  } else {
    BigNumber abn = a.i;
    BigNumber bbn = b.i;
    if (a.bn != nullptr) {
      abn = *a.bn;
    }
    if (b.bn != nullptr) {
      bbn = *b.bn;
    }
    return abn < bbn;
  }
}

bool operator>(Exponent a, Exponent b) { return b < a; }

bool operator<=(Exponent a, Exponent b) { return a < b || a == b; }

bool operator>=(Exponent a, Exponent b) { return a > b || a == b; }
