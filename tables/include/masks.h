// Precomputes the sliding-piece blocker masks for all 64 squares.
// bishopMasks[sq] contains all squares a bishop could reach from sq
// before hitting the board edge (excluding the outer rim).
// rookMasks[sq] contains the same for rook movement (ranks and files).
// These masks are used in magic bitboard generation to enumerate
// all possible blocker configurations for rooks and bishops.

#pragma once

#include "../../global/include/bitboard.h"

extern Bitboard bishopMasks[64]; // Mask Table for bishop
extern Bitboard rookMasks[64]; // Mask table for rook

void initMasks();