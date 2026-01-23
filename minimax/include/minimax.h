#pragma once

#include "../global/include/board.h"
#include "../evaluate/include/evaluate.h"
#include "../generatemoves/include/isgameover.h"
#include "../generatemoves/include/generatemoves.h"

int minimax(Board board, const int depht, int alpha, int beta, const bool maximizing);