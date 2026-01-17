#pragma once

#include "./attacks.h"
#include "../../global/include/bitboard.h"
#include "./masks.h"
#include "./magic.h"
#include "../../global/include/generatemovesvar.h"

inline Bitboard getBishopAttacks(int sq, Bitboard occ) {
    occ &= bishopMasks[sq];
    occ *= bishopMagics[sq];
    occ >>= (64 - bishopRelevantBits[sq]);
    return bishopAttacks[sq][occ];
}

inline Bitboard getRookAttacks(int sq, Bitboard occ) {
    occ &= rookMasks[sq];
    occ *= rookMagics[sq];
    occ >>= (64 - rookRelevantBits[sq]);
    return rookAttacks[sq][occ];
}

inline Bitboard getQueenAttacks(int sq, Bitboard occ) {
    return getBishopAttacks(sq, occ) | getRookAttacks(sq, occ);
}