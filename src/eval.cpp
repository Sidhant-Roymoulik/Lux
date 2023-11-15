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
Score eval_piece(EvalInfo& info, Board& board) {
    Score score;
    Bitboard copy = board.pieces(p, c);
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
Score eval_pawn(EvalInfo& info, Board& board) {
    Score score;
    Bitboard copy = board.pieces(PieceType::PAWN, c);

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
Score eval_king(EvalInfo& info, Board& board) {
    Score score;

    Square sq = board.kingSq(c);

    if (c == Color::WHITE) sq = sq ^ 56;
    score += PST[(int)PieceType::KING][sq];

    return score;
}

void eval_pieces(EvalInfo& info, Board& board) {
    info.score += eval_pawn<Color::WHITE>(info, board);
    info.score -= eval_pawn<Color::BLACK>(info, board);

    info.score += eval_piece<Color::WHITE, PieceType::KNIGHT>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::BISHOP>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::ROOK>(info, board);
    info.score += eval_piece<Color::WHITE, PieceType::QUEEN>(info, board);

    info.score -= eval_piece<Color::BLACK, PieceType::KNIGHT>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::BISHOP>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::ROOK>(info, board);
    info.score -= eval_piece<Color::BLACK, PieceType::QUEEN>(info, board);

    info.score += eval_king<Color::WHITE>(info, board);
    info.score -= eval_king<Color::BLACK>(info, board);
}

int evaluate(Board& board) {
    // Check for draw by insufficient material
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    eval_pieces(info, board);

    info.gamephase = std::clamp(info.gamephase, 0, 24);

    int score = (info.score.mg * info.gamephase + info.score.eg * (24 - info.gamephase)) / 24;

    return (board.sideToMove() == Color::WHITE ? score : -score);
}