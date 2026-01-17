#pragma once

#include "../../global/include/bitboard.h"
#include "../../global/include/board.h"

// Piece Tables
extern int MgPST[6][2][64];
extern int EgPST[6][2][64];


int position_eval_mg(const Board &board);
int position_eval_eg(const Board &board);