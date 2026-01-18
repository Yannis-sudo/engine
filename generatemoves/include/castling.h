#pragma once

#include "../../global/include/board.h"
#include "../../global/include/movelist.h"
#include "./attacks.h"
#include "./pawnattacks.h"
#include "./attacks.h"
#include "./lookup.h"

inline bool isSquareAttacked(int sq, const Board &board, Color attackingSide) noexcept
{
    if (knightAttacks[sq] & board.pieces[attackingSide][KNIGHT])
        return true; // KNIGHT
    if (kingAttacks[sq] & board.pieces[attackingSide][KING])
        return true; // KING
    if (attackingSide == WHITE)
    {
        if (pawnAttacksWhite[sq] & board.pieces[attackingSide][PAWN])
            return true; // PAWN WHITE
    }
    else
    {
        if (pawnAttacksBlack[sq] & board.pieces[attackingSide][PAWN])
            return true; // PAWN BLACK
    }
    const Bitboard bishopAtt = getBishopAttacks(sq, board.occupiedAll);
    if (bishopAtt & (board.pieces[attackingSide][BISHOP] | board.pieces[attackingSide][QUEEN]))
        return true; // BISHOP / QUEEN

    // ROOK / QUEEN
    const Bitboard rookAtt = getRookAttacks(sq, board.occupiedAll);
    if (rookAtt & (board.pieces[attackingSide][ROOK] | board.pieces[attackingSide][QUEEN]))
        return true;
    return false;
}

inline bool canCastle(const Board &board, const Color side, const bool kingSide) noexcept{
    if (kingSide) {
        if (side == WHITE) {
            if (!board.wks) return false;
            // Squares between e1 and g1 must be empty
            if (board.occupiedAll & ((1ULL << 5) | (1ULL << 6))) return false;
            // Squares e1, f1, g1 must not be under attack
            if (isSquareAttacked(4, board, BLACK) || isSquareAttacked(5, board, BLACK) || isSquareAttacked(6, board, BLACK)) return false;
            return true;
        }
        else {
            if (!board.bks) return false;
            // Squares between e8 and g8 must be empty
            if (board.occupiedAll & ((1ULL << 61) | (1ULL << 62))) return false;
            // Squares e8, f8, g8 must not be under attack
            if (isSquareAttacked(60, board, WHITE) || isSquareAttacked(61, board, WHITE) || isSquareAttacked(62, board, WHITE)) return false;
            return true;
        }
    }
    else {
        if (side == WHITE) {
            if (!board.wqs) return false;
            // Squares between e1 and c1 must be empty
            if (board.occupiedAll & ((1ULL << 1) | (1ULL << 2) | (1ULL << 3))) return false;
            // Squares e1, d1, c1 must not be under attack
            if (isSquareAttacked(4, board, BLACK) || isSquareAttacked(3, board, BLACK) || isSquareAttacked(2, board, BLACK)) return false;
            return true;
        }
        else {
            if (!board.bqs) return false;
            // Squares between e8 and c8 must be empty
            if (board.occupiedAll & ((1ULL << 57) | (1ULL << 58) | (1ULL << 59))) return false;
            // Squares e8, d8, c8 must not be under attack
            if (isSquareAttacked(60, board, WHITE) || isSquareAttacked(59, board, WHITE) || isSquareAttacked(58, board, WHITE)) return false;
            return true;
        }
    }
} 
void addCastlingMoves(const Board &board, MoveList &list) noexcept;