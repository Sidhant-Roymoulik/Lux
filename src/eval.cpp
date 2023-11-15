#include "eval.h"

#include "chess.hpp"
#include "eval.h"
#include "eval_constants.h"
#include "search.h"
#include "types.h"

using namespace chess;

Bitboard files[64], ranks[64];

void init_eval_tables() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 64; j++) {
            PST[i][j] += PieceValues[i];
        }
    }

    Bitboard file = 0x101010101010101, rank = 0xff00000000000000;

    for (int i = 0; i < 8; i++) {
        files[i] = file << i;
        for (int j = i; j < 64; j += 8) files[j] = files[i];
    }

    for (int i = 0; i < 64; i += 8) {
        ranks[i] = rank >> i;
        for (int j = 0; j < 8; j++) ranks[j] = ranks[i];
    }
}

template <Color c, PieceType p>
Score eval_piece(EvalInfo& info, SearchThread& st) {
    Score score;
    Bitboard copy = st.board.pieces(p, c);
    info.gamephase += PhaseValues[(int)p] * builtin::popcount(copy);

    if (p == PieceType::BISHOP && (copy & (copy - 1))) score += BishopPair;

    while (copy) {
        Square sq = builtin::poplsb(copy);

        if (p == PieceType::ROOK) {
            Bitboard file = files[(int)utils::squareFile(sq)];
            if (!(file & (info.pawn[0] | info.pawn[1]))) {
                score += OpenFile;
            } else if (!(file & info.pawn[(int)c])) {
                score += SemiOpenFile;
            }
        }

        if (c == Color::WHITE) sq = sq ^ 56;
        score += PST[(int)p][sq];
    }

    return score;
}

template <Color c>
Score eval_pawn(EvalInfo& info, SearchThread& st) {
    Score score;
    Bitboard copy = st.board.pieces(PieceType::PAWN, c);

    info.pawn[(int)c] = copy;

    // int count = builtin::popcount(copy & (attacks::pawnLeftAttacks<c>(copy) | attacks::pawnRightAttacks<c>(copy)));
    // score += PawnSupport * count;

    while (copy) {
        Square sq = builtin::poplsb(copy);

        // Bitboard file = files[(int)utils::squareFile(sq)];
        // if (builtin::popcount(copy & file) - 1) score += PawnDoubled;

        if (c == Color::WHITE) sq = sq ^ 56;
        score += PST[(int)PieceType::PAWN][sq];
    }

    return score;
}

template <Color c>
Score eval_king(EvalInfo& info, SearchThread& st) {
    Score score;

    Square sq = st.board.kingSq(c);

    if (c == Color::WHITE) sq = sq ^ 56;
    score += PST[(int)PieceType::KING][sq];

    return score;
}

void eval_pieces(EvalInfo& info, SearchThread& st) {
    info.score += eval_pawn<Color::WHITE>(info, st);
    info.score -= eval_pawn<Color::BLACK>(info, st);

    info.score += eval_piece<Color::WHITE, PieceType::KNIGHT>(info, st);
    info.score += eval_piece<Color::WHITE, PieceType::BISHOP>(info, st);
    info.score += eval_piece<Color::WHITE, PieceType::ROOK>(info, st);
    info.score += eval_piece<Color::WHITE, PieceType::QUEEN>(info, st);

    info.score -= eval_piece<Color::BLACK, PieceType::KNIGHT>(info, st);
    info.score -= eval_piece<Color::BLACK, PieceType::BISHOP>(info, st);
    info.score -= eval_piece<Color::BLACK, PieceType::ROOK>(info, st);
    info.score -= eval_piece<Color::BLACK, PieceType::QUEEN>(info, st);

    info.score += eval_king<Color::WHITE>(info, st);
    info.score -= eval_king<Color::BLACK>(info, st);
}

int evaluate(SearchThread& st) {
    // Check for draw by insufficient material
    if (st.board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    eval_pieces(info, st);

    info.gamephase = std::clamp(info.gamephase, 0, 24);

    int score = (info.score.mg * info.gamephase + info.score.eg * (24 - info.gamephase)) / 24;

    return (st.board.sideToMove() == Color::WHITE ? score : -score);
}