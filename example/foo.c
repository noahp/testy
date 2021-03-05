#include "testy.h"

int foo_multiply(int a, int b) {
  return a * b;
}

TEST(test_foo_multiply, { assert(foo_multiply(2, 3) == 6); })
