#pragma once

#include "../../global/include/board.h"
#include "../../global/include/movelist.h"
#include "./generatemoves.h"

bool insufficiant_material(const Board &board);

bool isCheck(const Board &board, Color side);

GameResult isGameOver(Board &board);