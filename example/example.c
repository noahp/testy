#include <stdio.h>

#include "foo.h"
#include "testy.h"

int square(int n) {
  return foo_multiply(n, n);
}

TEST(
    test_square,
    {
      assert(square(2) == 4);
      assert(square(3) == 9);
    }

    //! fake implemented here
    int foo_multiply(int a, int b) { return a * b; })

//! this one fails and we get a nice (?) core dump!
// TEST(test_square_fails, { assert(square(3) != 9); })

int main(int argc, char **argv) {
  (void)argc, (void)argc;
  printf("example main!\n");
  return 0;
}
