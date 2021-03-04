#include "testy.h"

int square(int n) { return n * n; }

TEST(test_square, {
    assert(square(2) == 4);
    assert(square(3) == 9);
})

//! this one fails and we get a nice (?) core dump!
// TEST(test_square_fails, { assert(square(3) != 9); })
