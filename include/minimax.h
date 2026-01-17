#pragma once

#include <iostream>
#include <limits>
#include <algorithm>

#include "../global/include/bitboard.h"
#include "../global/include/board.h"
#include "../global/include/movelist.h"
#include "../generatemoves/include/generatemoves.h"
#include "../evaluate/include/evaluate.h"
#include "../generatemoves/include/isgameover.h"

int negamax(Board &board, int depth, int alpha, int beta);