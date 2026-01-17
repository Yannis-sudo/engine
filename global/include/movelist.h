#pragma once

#include "./board.h"

const int MAX_MOVES = 256;

struct MoveList {
    Move moves[MAX_MOVES];
    Move legalMoves[MAX_MOVES];
    int count = 0;
    int count2 = 0;

    inline void add(const Move& m) {
        moves[count++] = m;
    }

    inline void addLegal(const Move& m) {
        legalMoves[count2++] = m;
    }
};