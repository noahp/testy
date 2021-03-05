#include "testy.h"

#include <stdio.h>
#include <stdlib.h>

struct testy_test {
  struct testy_test *next;
  const char *name;
  void (*func)(void);
  const char *file;
  int line;
};

struct testy_test *g_tests = NULL;

void testy_register(const char *name, void (*func)(void), const char *file,
                    int line) {
  struct testy_test *new_test;
  new_test = calloc(1, sizeof(*new_test));
  *new_test = (struct testy_test){
      .next = g_tests,
      .name = name,
      .func = func,
      .file = file,
      .line = line,
  };
  g_tests = new_test;
}

//! The testy main function is named '__wrap_main' so we can substitute it for
//! any potential REAL 'main' function that may exist in a file under test.
int __wrap_main(int argc, char **argv) {
  for (struct testy_test *test = g_tests; test; test = test->next) {
    printf("Running %s.%s:%d ... ", test->file, test->name, test->line);
    test->func();
    printf("PASS!\n");
  }

  return 0;
}
