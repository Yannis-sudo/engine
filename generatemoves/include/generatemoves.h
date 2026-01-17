#pragma once

#include "../../global/include/board.h"
#include "./attacks.h"
#include "./pawnattacks.h"
#include <iostream>
#include "../../global/include/movelist.h"
#include "./attacks.h"
#include "./lookup.h"
#include "../../global/include/makemove.h"
#include <thread>
#include <vector>

MoveList generateMoves(Board &board);
bool isSquareAttacked(int sq, const Board &board, Color attackingSide);