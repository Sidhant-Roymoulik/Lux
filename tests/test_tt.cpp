#include "framework.h"
#include "tt.h"

// Redirect stdout during Initialize() to suppress the size print.
// We simply call Initialize(1) and accept the one-line output.

int test_tt() {
    _pass = 0;
    _fail = 0;

    // --- Mate score normalization ---

    // score_to_tt: mate score is adjusted upward by ply
    CHECK_EQ(score_to_tt(MATE - 5, 3), MATE - 2);
    CHECK_EQ(score_to_tt(MATE_IN_MAX + 1, 5), MATE_IN_MAX + 6);

    // score_from_tt: inverse of score_to_tt
    CHECK_EQ(score_from_tt(MATE - 2, 3), MATE - 5);
    CHECK_EQ(score_from_tt(MATE_IN_MAX + 6, 5), MATE_IN_MAX + 1);

    // Mated scores
    CHECK_EQ(score_to_tt(-(MATE - 5), 3), -(MATE - 2));
    CHECK_EQ(score_from_tt(-(MATE - 2), 3), -(MATE - 5));

    // Normal scores pass through unchanged
    CHECK_EQ(score_to_tt(100, 10), 100);
    CHECK_EQ(score_from_tt(-300, 7), -300);
    CHECK_EQ(score_to_tt(0, 5), 0);

    // Roundtrip for mate score
    int original = MATE - 8;
    int ply      = 4;
    CHECK_EQ(score_from_tt(score_to_tt(original, ply), ply), original);

    // --- TT store / probe ---

    TranspositionTable tt;
    tt.Initialize(1);  // 1 MB; prints one line to stdout

    uint64_t key = 0xDEADBEEF12345678ULL;
    Board    b(chess::constants::STARTPOS);
    Move     move_a = uci::uciToMove(b, "e2e4");
    Move     move_b = uci::uciToMove(b, "d2d4");

    // Empty table: no hit
    bool ttHit = true;
    tt.probe_entry(key, ttHit);
    CHECK(!ttHit);
    CHECK_EQ(tt.probe_move(key), Move::NO_MOVE);

    // Store and probe back
    tt.store(key, FLAG_EXACT, move_a, 5, 100, 80);
    TTEntry& e = tt.probe_entry(key, ttHit);
    CHECK(ttHit);
    CHECK_EQ(e.score, 100);
    CHECK_EQ(e.eval, 80);
    CHECK_EQ(e.depth, 5);
    CHECK_EQ(e.flag, FLAG_EXACT);
    CHECK_EQ(tt.probe_move(key), move_a);

    // Higher depth replaces (non-exact flag)
    tt.store(key, FLAG_BETA, move_b, 8, 200, 90);
    e = tt.probe_entry(key, ttHit);
    CHECK(ttHit);
    CHECK_EQ(e.depth, 8);
    CHECK_EQ(e.score, 200);

    // Lower depth does NOT replace (non-exact flag, same key)
    tt.store(key, FLAG_BETA, move_a, 3, 50, 40);
    e = tt.probe_entry(key, ttHit);
    CHECK(ttHit);
    CHECK_EQ(e.depth, 8);    // unchanged
    CHECK_EQ(e.score, 200);  // unchanged

    // FLAG_EXACT always replaces regardless of depth
    tt.store(key, FLAG_EXACT, move_a, 2, 999, 0);
    e = tt.probe_entry(key, ttHit);
    CHECK(ttHit);
    CHECK_EQ(e.flag, FLAG_EXACT);
    CHECK_EQ(e.score, 999);
    CHECK_EQ(e.depth, 2);

    // Different key (low 16 bits differ) → no hit
    // key ^ 0xFFFF changes low 16 bits so uint16_t(key) != uint16_t(other_key)
    uint64_t other_key = key ^ 0xFFFFULL;
    tt.probe_entry(other_key, ttHit);
    CHECK(!ttHit);
    CHECK_EQ(tt.probe_move(other_key), Move::NO_MOVE);

    // Move preservation: a lower-depth store with NO_MOVE must not erase the
    // existing move when the depth criterion prevents replacement.
    // Reset table so we have a clean entry.
    tt.Initialize(1);
    tt.store(key, FLAG_BETA, move_b, 8, 100, 50);
    tt.store(key, FLAG_BETA, Move::NO_MOVE, 3, 0, 0);  // depth 3 < 8 → no replace
    CHECK_EQ(tt.probe_move(key), move_b);               // move_b must survive

    // Replacing a FLAG_ALPHA entry with a higher-depth FLAG_ALPHA entry
    tt.Initialize(1);
    tt.store(key, FLAG_ALPHA, move_a, 4, -50, 0);
    tt.store(key, FLAG_ALPHA, move_b, 6, -30, 0);  // depth 6 > 4 → replaces
    e = tt.probe_entry(key, ttHit);
    CHECK(ttHit);
    CHECK_EQ(e.depth, 6);
    CHECK_EQ(e.score, -30);

    return report("tt");
}
