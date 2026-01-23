#pragma once


#include "../global/include/bitboard.h"
#include "../global/include/board.h"
#include "../minimax/include/minimax.h"
#include "../generatemoves/include/generatemoves.h"
#include "../global/include/makemove.h"

#include <string>
#include <limits>
#include <iostream>

std::string bestmove(Board &board, bool maximizing, int depht);