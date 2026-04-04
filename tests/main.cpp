#include <cstdio>
#include "eval.h"

int test_types();
int test_tt();
int test_eval();
int test_time_manager();

int main() {
    // Required before any evaluate() calls
    init_eval_tables();

    int failures = 0;
    failures += test_types();
    failures += test_tt();
    failures += test_eval();
    failures += test_time_manager();

    if (failures > 0) {
        std::printf("\n%d test(s) FAILED\n", failures);
        return 1;
    }
    std::printf("\nAll tests passed\n");
    return 0;
}
