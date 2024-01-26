#include "eval.h"

#include "chess.hpp"
#include "eval.h"
#include "eval_constants.h"
#include "search.h"
#include "types.h"

using namespace chess;

void init_eval_tables() {
    for (int i = (int)PieceType::PAWN; i <= (int)PieceType::KING; i++) {
        for (int j = Square::SQ_A1; j <= Square::SQ_H8; j++) {
            PST[i][j] += PieceValues[i];
        }
    }
}

template <Color c>
Score eval_pawn(EvalInfo& info, Board& board) {
    Score score;
    Bitboard pawns = board.pieces(PieceType::PAWN, c);

    info.pawn[(int)c] = pawns;

    while (pawns) {
        Square sq = builtin::poplsb(pawns);

        if (c == Color::WHITE) sq = sq ^ 56;
        score += PST[(int)PieceType::PAWN][sq];
    }

    return score;
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
            Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(sq)];
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
Score eval_king(Board& board) {
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

    info.score += eval_king<Color::WHITE>(board);
    info.score -= eval_king<Color::BLACK>(board);
}

double eval_drawish(Board& board) {
    int occ = builtin::popcount(board.occ());

    if (occ == 4) {
        int white_knights = builtin::popcount(board.pieces(PieceType::KNIGHT, Color::WHITE));
        int black_knights = builtin::popcount(board.pieces(PieceType::KNIGHT, Color::BLACK));

        if (white_knights == 2 || black_knights == 2) return 0.0;
    }

    return 1.0;
}

int evaluate(Board& board) {
    // Check for draw by insufficient material
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    eval_pieces(info, board);

    info.gamephase = std::min(info.gamephase, 24);

    int score = (info.score.mg * info.gamephase + info.score.eg * (24 - info.gamephase)) / 24;

    score *= eval_drawish(board);

    return (board.sideToMove() == Color::WHITE ? score : -score);
}