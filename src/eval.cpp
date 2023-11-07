#include "eval.h"

#include "chess.hpp"
#include "eval_constants.h"
#include "search.h"
#include "types.h"

using namespace chess;

int evaluate(SearchThread& st) {
    // Check for draw by insufficient material
    if (st.board.isInsufficientMaterial()) return 0;

    Score score[2];
    int gamephase = 0;
    int turn      = (int)st.board.sideToMove();

    for (int color = 0; color < 2; color++) {
        for (int piece_type = 0; piece_type < 6; piece_type++) {
            Bitboard copy = st.board.pieces(PieceType(piece_type), Color(color));

            while (copy) {
                Square sq = builtin::poplsb(copy);

                if (!color) {
                    sq = sq ^ 56;
                }

                score[color] += PIECE_VALUES[piece_type] + PST[piece_type][sq];
                gamephase += GAMEPHASE[piece_type];
            }
        }
    }

    int mg_score = score[turn].mg - score[turn ^ 1].mg;
    int eg_score = score[turn].eg - score[turn ^ 1].eg;

    gamephase = std::clamp(gamephase, 0, 24);

    return (mg_score * gamephase + eg_score * (24 - gamephase)) / 24;
}