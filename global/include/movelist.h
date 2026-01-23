#pragma once

#include "./board.h"
#include "./makemove.h"

const int MAX_MOVES = 256;

struct MoveList {
    Move moves[MAX_MOVES];
    Move legalMoves[MAX_MOVES];
    int count = 0;
    int count2 = 0;

    inline void add(const Move& m) {
        moves[count++] = m;
    }

    inline void testAddLegal(const Move &m, Board b) {
        Bitboard kingBB = b.pieces[b.sideToMove][KING];
        const int kingSq = popLSB(kingBB);
        const Color side = (Color)(b.sideToMove ^ 2);
        makemove(b, m);
        if (!isSquareAttacked(b, b.sideToMove, kingSq)) {
            legalMoves[count++] = m;
        }
    }

    inline void addLegal(const Move& m) {
        legalMoves[count2++] = m;
    }
};