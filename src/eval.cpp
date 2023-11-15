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

Score eval_piece(EvalInfo& info, SearchThread& st, Color color, PieceType type) {
    Score score;
    Bitboard copy = st.board.pieces(type, color);
    info.gamephase += PhaseValues[(int)type] * builtin::popcount(copy);

    if (type == PieceType::BISHOP && (copy & (copy - 1))) score += BishopPair;

    while (copy) {
        Square sq = builtin::poplsb(copy);

        if (type == PieceType::ROOK) {
            Bitboard file = files[(int)utils::squareFile(sq)];
            if (!(file & (info.pawn[0] | info.pawn[1]))) {
                score += OpenFile;
            } else if (!(file & info.pawn[(int)color])) {
                score += SemiOpenFile;
            }
        }

        if (color == Color::WHITE) sq = sq ^ 56;
        score += PST[(int)type][sq];
    }

    return score;
}

Score eval_pawn(EvalInfo& info, SearchThread& st, Color color) {
    Score score;
    Bitboard copy = st.board.pieces(PieceType::PAWN, color);

    info.pawn[(int)color] = copy;

    while (copy) {
        Square sq = builtin::poplsb(copy);

        if (color == Color::WHITE) sq = sq ^ 56;
        score += PST[(int)PieceType::PAWN][sq];
    }

    return score;
}

Score eval_king(EvalInfo& info, SearchThread& st, Color color) {
    Score score;

    Square sq = st.board.kingSq(color);

    if (color == Color::WHITE) sq = sq ^ 56;
    score += PST[(int)PieceType::KING][sq];

    return score;
}

int evaluate(SearchThread& st) {
    // Check for draw by insufficient material
    if (st.board.isInsufficientMaterial()) return 0;

    EvalInfo info;
    Color turn = st.board.sideToMove(), other = ~turn;

    info.score += eval_pawn(info, st, turn);
    info.score -= eval_pawn(info, st, other);

    info.score += eval_piece(info, st, turn, PieceType::KNIGHT);
    info.score += eval_piece(info, st, turn, PieceType::BISHOP);
    info.score += eval_piece(info, st, turn, PieceType::ROOK);
    info.score += eval_piece(info, st, turn, PieceType::QUEEN);

    info.score -= eval_piece(info, st, other, PieceType::KNIGHT);
    info.score -= eval_piece(info, st, other, PieceType::BISHOP);
    info.score -= eval_piece(info, st, other, PieceType::ROOK);
    info.score -= eval_piece(info, st, other, PieceType::QUEEN);

    info.score += eval_king(info, st, turn);
    info.score -= eval_king(info, st, other);

    info.gamephase = std::clamp(info.gamephase, 0, 24);

    return (info.score.mg * info.gamephase + info.score.eg * (24 - info.gamephase)) / 24;
}