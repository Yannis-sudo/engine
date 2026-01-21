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
            if (isSquareAttacked(board, BLACK, 4) || isSquareAttacked(board, BLACK, 5) || isSquareAttacked(board, BLACK, 6)) return false;
            return true;
        }
        else {
            if (!board.bks) return false;
            // Squares between e8 and g8 must be empty
            if (board.occupiedAll & ((1ULL << 61) | (1ULL << 62))) return false;
            // Squares e8, f8, g8 must not be under attack
            if (isSquareAttacked(board, WHITE, 60) || isSquareAttacked(board, WHITE, 61) || isSquareAttacked(board, WHITE, 62)) return false;
            return true;
        }
    }
    else {
        if (side == WHITE) {
            if (!board.wqs) return false;
            // Squares between e1 and c1 must be empty
            if (board.occupiedAll & ((1ULL << 1) | (1ULL << 2) | (1ULL << 3))) return false;
            // Squares e1, d1, c1 must not be under attack
            if (isSquareAttacked(board, BLACK, 4) || isSquareAttacked(board, BLACK, 3) || isSquareAttacked(board, BLACK, 2)) return false;
            return true;
        }
        else {
            if (!board.bqs) return false;
            // Squares between e8 and c8 must be empty
            if (board.occupiedAll & ((1ULL << 57) | (1ULL << 58) | (1ULL << 59))) return false;
            // Squares e8, d8, c8 must not be under attack
            if (isSquareAttacked(board, WHITE, 60) || isSquareAttacked(board, WHITE, 59) || isSquareAttacked(board, WHITE, 58)) return false;
            return true;
        }
    }
} 
void addCastlingMoves(const Board &board, MoveList &list) noexcept;