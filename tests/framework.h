#pragma once

#include <cstdio>

static int _pass = 0;
static int _fail = 0;

#define CHECK(expr)                                                             \
    do {                                                                        \
        if (expr) {                                                             \
            _pass++;                                                            \
        } else {                                                                \
            _fail++;                                                            \
            std::printf("  FAIL: %s  (%s:%d)\n", #expr, __FILE__, __LINE__);  \
        }                                                                       \
    } while (0)

#define CHECK_EQ(a, b) CHECK((a) == (b))

// Call at the end of each test function. Returns the failure count for that suite.
inline int report(const char* suite) {
    std::printf("%s: %d passed", suite, _pass);
    if (_fail > 0) std::printf(", %d FAILED", _fail);
    std::printf("\n");
    return _fail;
}
