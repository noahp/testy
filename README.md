# testy test framework (?)

This is a real bad c test framework that has 1 possibly redeeming quality:

1. define your test functions in line with the function under test!

Example:

```c
#include "testy.h"

int multiply(int a, int b) {
    return a * b;
}

// test the above multiply function
TEST(multiply, {
    assert(multiply(2, 3) == 6);
}
)
```

Found the idea in this nice writeup, see link below or [`testy.h`](testy.h).

https://blog.noctua-software.com/c-unit-tests-constructor-attribute.html

## Usage

1. Copy `testy.c` + `testy.h` + `testy.py` into your project
2. Implement some tests (see [`example/example.c`](example/example.c) for an
   example). You may need to include mocks.
3. Run `./testy.py` passing your c file as argument.

## Note on mocks

To limit the amount of effort spent mocking, I'm using a wonderful idea from
here:

https://github.com/jwgrenning/gen-xfakes

I capture linker output and produce a stub for any missing definitions
containing a single `assert(0)`. If any of the generated stubs are executed
during a test, it will crash/fail, and a proper mock will need to be included in
a `TEST()` statement (see [`example/example.c`](example/example.c) for an
example).

## Note on `main`

The testy `main` function is named `__wrap_main` to take advantage of the ld
`--wrap` argument; this allows me to substitute the testy main in place of any
potential real main function in the file under test (it also works correctly if
there's no `__real_main` function present).

## TODO

- support injecting more compiler flags (it might make more sense to hook into
  the normal project's build command, like how scan-build operates, and get all
  the c files and compiler flags from there)
- run in parallel + output summary? (can be done via gnu parallel as-is 😬)
- build caching (eg via Make?)?
- 🌈 colors 🌈 ?
- coverage (gcov)
