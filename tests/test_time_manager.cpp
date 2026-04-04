#include "framework.h"
#include "time_manager.h"

int test_time_manager() {
    _pass = 0;
    _fail = 0;

    constexpr int OVERHEAD = 20;

    // movetime mode
    {
        Time_Manager tm;
        tm.movetime   = 1000;
        tm.start_time = now();
        tm.set_time(Color::WHITE);
        CHECK_EQ(tm.stoptime_max, 1000 - OVERHEAD);
    }

    // movestogo mode
    {
        Time_Manager tm;
        tm.wtime      = 60000;
        tm.movestogo  = 30;
        tm.start_time = now();
        tm.set_time(Color::WHITE);
        CHECK_EQ(tm.stoptime_max, 60000 / 30 - OVERHEAD);
    }

    // movestogo mode, black to move
    {
        Time_Manager tm;
        tm.btime      = 30000;
        tm.movestogo  = 15;
        tm.start_time = now();
        tm.set_time(Color::BLACK);
        CHECK_EQ(tm.stoptime_max, 30000 / 15 - OVERHEAD);
    }

    // regular mode (no movetime, no movestogo), with increment
    {
        Time_Manager tm;
        tm.wtime      = 60000;
        tm.winc       = 500;
        tm.start_time = now();
        tm.set_time(Color::WHITE);
        CHECK_EQ(tm.stoptime_max, 60000 / 30 - OVERHEAD + 500);
    }

    // regular mode, no increment
    {
        Time_Manager tm;
        tm.wtime      = 30000;
        tm.start_time = now();
        tm.set_time(Color::WHITE);
        CHECK_EQ(tm.stoptime_max, 30000 / 30 - OVERHEAD);
    }

    // check_time() returns false when plenty of time remains
    {
        Time_Manager tm;
        tm.end_time = now() + 60000;
        CHECK(!tm.check_time());
    }

    // check_time() returns true when deadline has passed
    {
        Time_Manager tm;
        tm.end_time = now() - 1;
        CHECK(tm.check_time());
    }

    return report("time_manager");
}
