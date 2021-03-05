
#if defined(TESTY_UNIT_TEST)
#include <assert.h>
void testy_register(const char *name, void (*func)(void), const char *file,
                    int line);

//! Generate the test function body and the constructor that registers it with
//! the testy list of tests
#define TEST(func_, contents_)                                            \
    static void func_(void) contents_                                     \
        __attribute__((constructor)) static void reg_test_##func_(void) { \
        testy_register(#func_, func_, __FILE__, __LINE__);                \
    }

//! Generate an exploding fake for linker misses
#define TESTY_EXPLODING_FAKE(name) \
  __attribute__((weak)) void name(void) { assert(0 && "exploding fake!"); }

#else
#define TEST(func_, contents_)
#endif
