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

int main(int argc, char **argv) {
    for (struct testy_test *test = g_tests; test; test = test->next) {
        printf("Running %s.%s:%d ...\n", test->file, test->name, test->line);
        test->func();
    }
}
