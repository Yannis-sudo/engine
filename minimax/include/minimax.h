#pragma once

#include "../global/include/board.h"
#include "../evaluate/include/evaluate.h"
#include "../generatemoves/include/isgameover.h"
#include "../generatemoves/include/generatemoves.h"

#include <cstdint>

int minimax(Board board, const int depht, int alpha, int beta, const bool maximizing);