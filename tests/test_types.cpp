#include "framework.h"
#include "types.h"

int test_types() {
    _pass = 0;
    _fail = 0;

    // Basic roundtrip
    int packed = S(100, 200);
    CHECK_EQ(mg_score(packed), 100);
    CHECK_EQ(eg_score(packed), 200);

    // Zero
    CHECK_EQ(S(0, 0), 0);
    CHECK_EQ(mg_score(0), 0);
    CHECK_EQ(eg_score(0), 0);

    // Negative values
    packed = S(-50, -100);
    CHECK_EQ(mg_score(packed), -50);
    CHECK_EQ(eg_score(packed), -100);

    // Mixed signs
    packed = S(300, -150);
    CHECK_EQ(mg_score(packed), 300);
    CHECK_EQ(eg_score(packed), -150);

    // int16_t boundary values
    packed = S(32767, -32768);
    CHECK_EQ(mg_score(packed), 32767);
    CHECK_EQ(eg_score(packed), -32768);

    // Typical eval constant values survive roundtrip
    packed = S(274, 414);  // knight material
    CHECK_EQ(mg_score(packed), 274);
    CHECK_EQ(eg_score(packed), 414);

    packed = S(945, 1342);  // queen material
    CHECK_EQ(mg_score(packed), 945);
    CHECK_EQ(eg_score(packed), 1342);

    // Mate constant sanity
    CHECK(MATE > 0);
    CHECK(MATE_IN_MAX < MATE);
    CHECK(MATED_IN_MAX == -MATE_IN_MAX);
    CHECK(MATE - MAX_PLY == MATE_IN_MAX);

    return report("types");
}
