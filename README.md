# testy test framework (?)

This is a real bad c test framework that has 1 possibly redeeming quality:

1. define your test functions in line with the function under test!

Example:

```c
int multiply(int a, int b) {
    return a * b;
}

TEST(multiply, {
    assert(multiply(2, 3) == 6);
}
)
```

Found the idea in this nice writeup, see there or the [`testy.h`](testy.h).

https://blog.noctua-software.com/c-unit-tests-constructor-attribute.html

## Usage

1. Copy `testy.c` + `testy.h` into your project
2. Add a test binary compilation that builds your source files, omitting your
   `main()` (you could use a preprocessor define to skip it, for example, and
   reuse your normal build rule) and including `testy.c`, and runs the resultant
   binary
