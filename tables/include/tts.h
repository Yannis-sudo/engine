// This file contains the Transposiotion Tables
// The transposition Tables are used in minimax() to save evals

#pragma once

#include <cstdint>

#include "../../global/include/board.h"

enum TTFlag
{
    TT_EXACT,
    TT_ALPHA,
    TT_BETA
};

struct TTEntry
{
    uint64_t key = 0;
    int score = 0;
    int depth = 0;
    TTFlag flag = TT_EXACT;
    Move bestMove;
};

constexpr int TT_SIZE = 1 << 20; // 1M entries
TTEntry TT[TT_SIZE];

inline TTEntry &probeTT(uint64_t key)
{
    return TT[key & (TT_SIZE - 1)];
}
