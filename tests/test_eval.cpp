#include "framework.h"
#include "eval.h"

// init_eval_tables() is called once in main() before these tests run.

int test_eval() {
    _pass = 0;
    _fail = 0;

    // Insufficient material: KvK → 0
    {
        Board b("k7/8/8/8/8/8/8/7K w - - 0 1");
        CHECK_EQ(evaluate(b), 0);
    }

    // Start position is symmetric → 0
    {
        Board b(chess::constants::STARTPOS);
        CHECK_EQ(evaluate(b), 0);
    }

    // White has an extra queen → positive from white's perspective (white to move)
    {
        Board b("k7/8/8/8/8/8/8/KQ6 w - - 0 1");
        CHECK(evaluate(b) > 0);
    }

    // Color-flip: same structure but black has the queen (black to move).
    // Correct mirror: swap colors + flip ranks vertically.
    // "k7/8/8/8/8/8/8/KQ6 w" flips to "kq6/8/8/8/8/8/8/K7 b"
    // (black king a8, black queen b8, white king a1 — not h1)
    {
        Board b("kq6/8/8/8/8/8/8/K7 b - - 0 1");
        CHECK(evaluate(b) > 0);
    }

    // Mirror symmetry: both positions should give identical scores
    {
        Board white_up("k7/8/8/8/8/8/8/KQ6 w - - 0 1");
        Board black_up("kq6/8/8/8/8/8/8/K7 b - - 0 1");
        CHECK_EQ(evaluate(white_up), evaluate(black_up));
    }

    // Extra rook: white has rook + king vs king → positive, and less than a queen
    {
        int rook_adv  = evaluate(Board("k7/8/8/8/8/8/8/KR6 w - - 0 1"));
        int queen_adv = evaluate(Board("k7/8/8/8/8/8/8/KQ6 w - - 0 1"));
        CHECK(rook_adv > 0);
        CHECK(rook_adv < queen_adv);
    }

    // Symmetry with rooks: same structure, flipped colors
    // "k7/.../KR6 w" flips to "kr6/.../K7 b" (white king stays on a1, not h1)
    {
        Board white_up("k7/8/8/8/8/8/8/KR6 w - - 0 1");
        Board black_up("kr6/8/8/8/8/8/8/K7 b - - 0 1");
        CHECK_EQ(evaluate(white_up), evaluate(black_up));
    }

    // Piece count scales eval: two extra queens > one extra queen
    {
        int one_queen = evaluate(Board("k7/8/8/8/8/8/8/KQ6 w - - 0 1"));
        int two_queen = evaluate(Board("k7/8/8/8/8/8/8/KQQ5 w - - 0 1"));
        CHECK(two_queen > one_queen);
    }

    return report("eval");
}
