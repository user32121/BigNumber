#include <limits>

#include "BigNumber.h"

int main(int, char const **) {
  BigNumber n{1, 1};
  std::cout << n << " (1e1)" << std::endl;
  n = n + 1;
  std::cout << n << std::endl;
  n += 1;
  std::cout << n << std::endl;
  ++n;
  std::cout << n << std::endl;
  n -= 10;
  std::cout << n << std::endl;
  n -= 10;
  std::cout << n << std::endl;
  n -= -7.5;
  std::cout << n << std::endl;
  n -= 0.499;
  std::cout << n << std::endl;

  std::cout << std::endl;
  n = 101;
  std::cout << n << " (101)" << std::endl;
  for (size_t i = 0; i < 10; i++) {
    n += n;
    std::cout << n << std::endl;
  }

  n = 5;
  std::cout << std::endl;
  for (size_t i = 0; i < 10; i++) {
    --n;
    std::cout << n << std::endl;
  }

  std::cout << std::endl;
  n = 1e100;
  std::cout << n << " (1e100)" << std::endl;
  n = std::numeric_limits<double>::max();
  std::cout << n << " (double max)" << std::endl;
  n = std::numeric_limits<double>::epsilon();
  std::cout << n << " (double epsilon)" << std::endl;

  std::cout << std::endl;
  n = 1e-100;
  std::cout << n << " (1e-100)" << std::endl;
  while (n.exponent < 1000) {
    n *= 3;
    std::cout << n << std::endl;
  }
  BigNumber max = 1e10;
  while (n.exponent < max) {
    n *= n;
    std::cout << n << std::endl;
  }

  std::cout << std::endl;
  n = BigNumber{1, 420};
  BigNumber n2 = {3, 69};
  std::cout << "pow(" << n << "," << n2 << ")" << std::endl;
  std::cout << pow(n, n2) << std::endl;
  std::cout << "pow(pow(" << n << "," << n << "),pow(" << n2 << "," << n2
            << "))" << std::endl;
  std::cout << pow(pow(n, n), pow(n2, n2)) << std::endl;

  return 0;
}
