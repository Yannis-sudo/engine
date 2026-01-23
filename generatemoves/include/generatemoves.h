#pragma once

// Includes
#include <iostream>

// From global
#include "../../global/include/board.h"
#include "../../global/include/movelist.h"
#include "../../global/include/makemove.h"
// From tables
#include "../../tables/include/attacks.h"
#include "../../tables/include/lookup.h"
// From generatemoves
#include "./pawnattacks.h"
#include "./castling.h"

MoveList generateMoves(Board &board);
MoveList generateCaptures(Board &board); // For Q-Search. No legal Check!