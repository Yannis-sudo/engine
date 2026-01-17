#pragma once

#include "./bitboard.h"
#include "./masks.h"
#include "./magic.h"
#include "../../global/include/generatemovesvar.h"

extern Bitboard knightAttacks[64];
extern Bitboard kingAttacks[64];

extern Bitboard bishopAttacks[64][512];
extern Bitboard rookAttacks[64][4096];

extern Bitboard pawnAttacksWhite[64];
extern Bitboard pawnAttacksBlack[64];


void initAttackTable();

Bitboard computeBishopTable(int sq, Bitboard occ);
Bitboard computeRookTable(int sq, Bitboard occ);

Bitboard maskOccupancy(int index, Bitboard mask);
void initBishopRookTables();

void initPawnAttacks();