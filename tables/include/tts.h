// This file contains the Transposiotion Tables
// The transposition Tables are used in minimax() to save evals

#pragma once

#include <cstdint>

#include "../../global/include/board.h"

enum TTFlag : uint8_t
{
    TT_EXACT,
    TT_ALPHA,
    TT_BETA
};

struct TT_Entry {
    uint64_t key = 0;
    int16_t score = 0;
    int16_t depht = -1;
    TTFlag flag = TT_EXACT;
    Move bestMove;
};

constexpr int TT_SIZE = 1 << 20; // 1M
TT_Entry TT[TT_SIZE];

inline TT_Entry& ttProbeSlot(uint64_t key) {
    return TT[key & (TT_SIZE - 1)];
}