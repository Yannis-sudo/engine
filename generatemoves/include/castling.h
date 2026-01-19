#pragma once

#include "../../global/include/board.h"
#include "../../global/include/movelist.h"
#include "./pawnattacks.h"
#include "../../tables/include/attacks.h"
#include "../../tables/include/lookup.h"

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