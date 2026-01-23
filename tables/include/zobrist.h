#pragma once

#include <cstdint>
#include "../../global/include/board.h"

extern uint64_t zobristPiece[2][6][64];
extern uint64_t zobristSide;
extern uint64_t zobristCastling[16];
extern uint64_t zobristEnPassant[64];

void initZobrist();
uint64_t computeZobrist(const Board &b);
