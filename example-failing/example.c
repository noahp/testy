#include "testy.h"

int add(int a, int b) {
  return a + b;
}

TEST(add, {
  // intentionally failing assert to verify this test statement fails
  assert(add(1, 2) == 4);
})
