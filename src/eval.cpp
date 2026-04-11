#include "eval.h"

using namespace chess;

#define TraceIncr(parameter)
#define TraceAdd(parameter)

Bitboard passed_pawn_mask[2][64], pawn_isolated_mask[64], outpost_mask[2];

void init_eval_tables() {
    // Bake material into PST so pst[piece][sq] is the full piece+position score.
    for (int piece_type = static_cast<int>(PieceType::PAWN); piece_type <= static_cast<int>(PieceType::KING);
         piece_type++) {
        for (int sq = 0; sq < 64; sq++) {
            pst[piece_type][sq] += material[piece_type];
        }
    }

    outpost_mask[0] = attacks::MASK_RANK[4] | attacks::MASK_RANK[5] | attacks::MASK_RANK[6] | attacks::MASK_RANK[7];
    outpost_mask[1] = attacks::MASK_RANK[0] | attacks::MASK_RANK[1] | attacks::MASK_RANK[2] | attacks::MASK_RANK[3];

    for (int i = 0; i < 64; i++) {
        Bitboard file = attacks::MASK_FILE[static_cast<int>(Square(i).file())];

        pawn_isolated_mask[i] = attacks::shift<Direction::EAST>(file) | attacks::shift<Direction::WEST>(file);

        passed_pawn_mask[0][i] = file | attacks::shift<Direction::EAST>(file) | attacks::shift<Direction::WEST>(file);
        passed_pawn_mask[1][i] = passed_pawn_mask[0][i];

        // Shift until the pawn's own square is excluded, leaving only squares ahead of it.
        while (passed_pawn_mask[0][i] & (1ULL << i)) {
            passed_pawn_mask[0][i] = attacks::shift<Direction::NORTH>(passed_pawn_mask[0][i]);
        }
        while (passed_pawn_mask[1][i] & (1ULL << i)) {
            passed_pawn_mask[1][i] = attacks::shift<Direction::SOUTH>(passed_pawn_mask[1][i]);
        }
    }
}

template <Color::underlying c>
int black_relative_square(Square sq) {
    return (c == Color::WHITE) ? sq.index() ^ 56 : sq.index();
}

template <Color::underlying c>
int white_relative_square(Square sq) {
    return (c == Color::BLACK) ? sq.index() ^ 56 : sq.index();
}

template <Color::underlying c>
Bitboard get_pawn_attacks(Bitboard& pawns) {
    return attacks::pawnLeftAttacks<c>(pawns) | attacks::pawnRightAttacks<c>(pawns);
}

template <Color::underlying c>
int eval_pawn(EvalInfo& info, const Board& board) {
    int score = 0, count = 0;
    Bitboard pawn_bb = board.pieces(PieceType::PAWN, c);

    Bitboard phalanx_pawns = pawn_bb & attacks::shift<Direction::WEST>(pawn_bb);

    // pawn_doubled[0] = pawn directly ahead; [1] = pawn two squares ahead (potential doubling)
    count = (pawn_bb & attacks::shift<Direction::NORTH>(pawn_bb)).count();
    score += pawn_doubled[0] * count;
    TraceAdd(pawn_doubled[0]);

    count = (pawn_bb & attacks::shift<Direction::NORTH>(attacks::shift<Direction::NORTH>(pawn_bb))).count();
    score += pawn_doubled[1] * count;
    TraceAdd(pawn_doubled[1]);

    count = (pawn_bb & get_pawn_attacks<~c>(pawn_bb)).count();
    score += pawn_support * count;
    TraceAdd(pawn_support);

    while (phalanx_pawns) {
        Square sq = Square(phalanx_pawns.pop());
        score += pawn_phalanx[white_relative_square<c>(sq) >> 3];  // >> 3 extracts rank from square index
        TraceIncr(pawn_phalanx[white_relative_square<c>(sq) >> 3]);
    }

    while (pawn_bb) {
        Square sq = Square(pawn_bb.pop());

        if (!(pawn_isolated_mask[sq.index()] & info.pawn[static_cast<int>(c)])) {
            score += pawn_isolated;
            TraceIncr(pawn_isolated);
        }

        if (!(passed_pawn_mask[static_cast<int>(c)][sq.index()] & info.pawn[static_cast<int>(~c)])) {
            int protectors = (info.pawn[static_cast<int>(c)] & attacks::pawn(~c, sq)).count();
            score += pawn_passed[protectors][white_relative_square<c>(sq) >> 3];
            TraceIncr(pawn_passed[protectors][white_relative_square<c>(sq) >> 3]);
        }

        score += pst[static_cast<int>(PieceType::PAWN)][black_relative_square<c>(sq)];
        TraceIncr(pst[static_cast<int>(PieceType::PAWN)][black_relative_square<c>(sq)]);
        TraceIncr(material[0]);
    }

    return score;
}

template <Color::underlying c, PieceType::underlying p>
int eval_piece(EvalInfo& info, const Board& board) {
    int score = 0, count = 0;
    Bitboard piece_bb = board.pieces(p, c);

    const Direction DOWN = c == Color::WHITE ? Direction::SOUTH : Direction::NORTH;

    info.gamephase += phase_values[static_cast<int>(p)] * piece_bb.count();

    if (p == PieceType::BISHOP && piece_bb.count() >= 2) {
        score += bishop_pair;
        TraceIncr(bishop_pair);
    }

    if (p == PieceType::KNIGHT || p == PieceType::BISHOP) {
        count = (piece_bb & attacks::shift<DOWN>(info.pawn[static_cast<int>(c)])).count();
        score += minor_behind_pawn * count;
        TraceAdd(minor_behind_pawn);

        count = (piece_bb & info.pawn_attacks[static_cast<int>(c)] & outpost_mask[static_cast<int>(c)]).count();
        score += outpost * count;
        TraceAdd(outpost);
    }

    while (piece_bb) {
        Square sq = Square(piece_bb.pop());

        if (p == PieceType::ROOK) {
            Bitboard file = attacks::MASK_FILE[static_cast<int>(sq.file())];
            if (!(file & info.pawn[static_cast<int>(c)])) {
                if (!(file & info.pawn[static_cast<int>(~c)])) {
                    score += open_file;
                    TraceIncr(open_file);
                } else {
                    score += semi_open_file;
                    TraceIncr(semi_open_file);
                }
            }
        }

        if (info.pawn[static_cast<int>(~c)] & attacks::pawn(c, sq)) {
            score += attacked_by_pawn[static_cast<int>(p)];
            TraceIncr(attacked_by_pawn[static_cast<int>(p)]);
        }

        // Attack squares for mobility; excludes own pieces and pawn-controlled squares
        Bitboard attack_bb = 0;
        if (p == PieceType::KNIGHT)
            attack_bb = attacks::knight(sq);
        else if (p == PieceType::BISHOP)
            attack_bb = attacks::bishop(sq, board.occ());
        else if (p == PieceType::ROOK)
            attack_bb = attacks::rook(sq, board.occ());
        else if (p == PieceType::QUEEN)
            attack_bb = attacks::queen(sq, board.occ());

        score += mobility[static_cast<int>(p) - 1]
                         [(attack_bb & ~board.us(c) & ~info.pawn_attacks[static_cast<int>(~c)]).count()];
        TraceIncr(mobility[static_cast<int>(p) - 1]
                          [(attack_bb & ~board.us(c) & ~info.pawn_attacks[static_cast<int>(~c)]).count()]);

        score += pst[static_cast<int>(p)][black_relative_square<c>(sq)];
        TraceIncr(pst[static_cast<int>(p)][black_relative_square<c>(sq)]);
        TraceIncr(material[static_cast<int>(p)]);
    }

    return score;
}

template <Color::underlying c>
int eval_king(EvalInfo& info, const Board& board) {
    int score = 0, count = 0;
    Bitboard king_bb = board.pieces(PieceType::KING, c);
    Square king_sq   = Square(king_bb.pop());

    // Queen-map from king square measures how exposed the king is
    Bitboard attack_bb = attacks::queen(king_sq, board.occ());

    score += king_open[(attack_bb & ~board.us(c) & ~info.pawn_attacks[static_cast<int>(~c)]).count()];
    TraceIncr(king_open[(attack_bb & ~board.us(c) & ~info.pawn_attacks[static_cast<int>(~c)]).count()]);

    if (attacks::king(king_sq) & info.pawn[static_cast<int>(~c)]) {
        score += king_att_pawn;
        TraceIncr(king_att_pawn);
    }

    count = (passed_pawn_mask[static_cast<int>(c)][king_sq.index()] & info.pawn[static_cast<int>(c)]).count();
    score += king_shelter * count;
    TraceAdd(king_shelter);

    score += pst[static_cast<int>(PieceType::KING)][black_relative_square<c>(king_sq)];
    TraceIncr(pst[static_cast<int>(PieceType::KING)][black_relative_square<c>(king_sq)]);

    return score;
}

int eval_pieces(EvalInfo& info, const Board& board) {
    return eval_pawn<Color::WHITE>(info, board) - eval_pawn<Color::BLACK>(info, board) +

           eval_piece<Color::WHITE, PieceType::KNIGHT>(info, board) +
           eval_piece<Color::WHITE, PieceType::BISHOP>(info, board) +
           eval_piece<Color::WHITE, PieceType::ROOK>(info, board) +
           eval_piece<Color::WHITE, PieceType::QUEEN>(info, board) -

           eval_piece<Color::BLACK, PieceType::KNIGHT>(info, board) -
           eval_piece<Color::BLACK, PieceType::BISHOP>(info, board) -
           eval_piece<Color::BLACK, PieceType::ROOK>(info, board) -
           eval_piece<Color::BLACK, PieceType::QUEEN>(info, board) +

           eval_king<Color::WHITE>(info, board) - eval_king<Color::BLACK>(info, board);
}

void init_eval_info(EvalInfo& info, const Board& board) {
    info.pawn[0]         = board.pieces(PieceType::PAWN, Color::WHITE);
    info.pawn[1]         = board.pieces(PieceType::PAWN, Color::BLACK);
    info.pawn_attacks[0] = get_pawn_attacks<Color::WHITE>(info.pawn[0]);
    info.pawn_attacks[1] = get_pawn_attacks<Color::BLACK>(info.pawn[1]);
}

double endgame_scale(EvalInfo& info, int score) {
    // 128 normalises to [0.0, 1.0]: 0 missing pawns → 1.0, 8 missing → 0.0
    int num_missing_stronger_pawns = 8 - info.pawn[score < 0].count();
    return (128 - num_missing_stronger_pawns * num_missing_stronger_pawns) / 128.0;
}

int evaluate(const Board& board) {
    if (board.isInsufficientMaterial()) return 0;

    EvalInfo info;

    init_eval_info(info, board);

    int score = eval_pieces(info, board);

    int gamephase = std::min(info.gamephase, 24);  // 24 = full opening material

    score = (mg_score(score) * gamephase + eg_score(score) * (24 - gamephase) * endgame_scale(info, score)) / 24;

    return (board.sideToMove() == Color::WHITE ? score : -score);
}
