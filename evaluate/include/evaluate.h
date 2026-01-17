#pragma once

#include "../../global/include/bitboard.h"
#include "../../global/include/board.h"
#include "./gamestage.h"
#include "./positioneval.h"

// Evaluate
static const int pieceValueMg[6] = {
    82, // PAWN
    337, // KNIGHT
    365, // BISHOP
    477, // ROOK
    1025, // QUEEN
    0, // KING
};

static const int pieceValueEg[6] = {
    94, // PAWN
    281, // KNIGHT
    297, // BISHOP
    512, // ROOK
    936, // QUEEN
    0, // KING
};

int evaluateMG(const Board &board);
int evaluateEG(const Board &board);

int evaluate(const Board &board);