#include "eval.h"

#include "eval_constants.h"

using namespace chess;

void init_eval_tables() {
    for (int i = (int)PieceType::PAWN; i <= (int)PieceType::KING; i++) {
        for (int j = Square::SQ_A1; j <= Square::SQ_H8; j++) {
            pst[i][j] += material[i];
        }
    }
}

template <Color c>
int eval_pawn(EvalInfo& info, Board& board) {
    int score      = 0;
    Bitboard pawns = board.pieces(PieceType::PAWN, c);

    info.pawn[(int)c] = pawns;

    while (pawns) {
        Square sq = builtin::poplsb(pawns);

        if (c == Color::WHITE) sq = sq ^ 56;
        score += pst[(int)PieceType::PAWN][sq];
    }

    return score;
}

template <Color c, PieceType p>
int eval_piece(EvalInfo& info, Board& board) {
    int score     = 0;
    Bitboard copy = board.pieces(p, c);
    info.gamephase += phase_values[(int)p] * builtin::popcount(copy);

    if (p == PieceType::BISHOP && (copy & (copy - 1))) score += bishop_pair;

    while (copy) {
        Square sq = builtin::poplsb(copy);

        if (p == PieceType::ROOK) {
            Bitboard file = attacks::MASK_FILE[(int)utils::squareFile(sq)];
            if (!(file & (info.pawn[0] | info.pawn[1]))) {
                score += open_file;
            } else if (!(file & info.pawn[(int)c])) {
                score += semi_open_file;
            }
        }

        if (c == Color::WHITE) sq = sq ^ 56;
        score += pst[(int)p][sq];
    }

    return score;
}

template <Color c>
int eval_king(Board& board) {
    int score = 0;

    Square sq = board.kingSq(c);

    if (c == Color::WHITE) sq = sq ^ 56;
    score += pst[(int)PieceType::KING][sq];

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

int evaluate(Board& board) {
    // Check for draw by insufficient material
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    eval_pieces(info, board);

    info.gamephase = std::min(info.gamephase, 24);

    int score = (mg_score(info.score) * info.gamephase + eg_score(info.score) * (24 - info.gamephase)) / 24;

    return (board.sideToMove() == Color::WHITE ? score : -score);
}