// This file provides the core magic-bitboard attack lookup functions for
// bishops, rooks, and queens. Each function takes a square and an occupancy
// bitboard, applies the appropriate blocker mask, multiplies it by the
// precomputed magic number, and shifts the result to obtain a perfect hash
// index into the attack tables.
//
// getBishopAttacks() and getRookAttacks() return the sliding attacks for the
// given square under the current board occupancy. getQueenAttacks() simply
// combines both results. These functions are used heavily during move
// generation and allow O(1) retrieval of sliding piece attacks.

#pragma once

#include "../../global/include/bitboard.h"
#include "./masks.h"
#include "./magic.h"
#include "../../global/include/generatemovesvar.h"
#include "./attacks.h"

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