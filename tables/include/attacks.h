#pragma once

// Init Attack Tables for every piece
// Define Attack Tables

// Includes
#include "../../global/include/bitboard.h"
#include "../../global/include/generatemovesvar.h"
#include "./magic.h"

extern Bitboard bishopAttacks[64][1024]; // Attack Table for Bishop
extern Bitboard rookAttacks[64][4096]; // Attack Table for Rook
extern Bitboard knightAttacks[64]; // Attack Table for Knight
extern Bitboard kingAttacks[64]; // Attack Table for Rook
extern Bitboard pawnAttacksWhite[64]; // Attack Table for white pawns (Only attacks not moves forward)
extern Bitboard pawnAttacksBlack[64]; // Attack Table for black pawns (Only attacks not moves forward)

// Compute rook and bishop tables
Bitboard computeBishopTable(int sq, Bitboard occ);
Bitboard computeRookTable(int sq, Bitboard occ);

Bitboard maskOccupancy(int index, Bitboard mask); // Generates an occupancy bitboard by selecting subsets of the mask based on the index bits.

void initBishopRookTables(); // Init the attack table for bishop and rook (and queen)
void initAttackTable(); // Init the attack table for the knight and the king
void initPawnAttacks(); // Init the attack table for the pawn attacks
