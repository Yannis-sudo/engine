#include "../include/castling.h"



void addCastlingMoves(const Board &board, MoveList &list) noexcept {
    if (board.sideToMove == WHITE) {
        if (canCastle(board, WHITE, true)) {
            list.add({4, 6, KING, false, false, false, true}); // e1 to g1
        }
        if (canCastle(board, WHITE, false)) {
            list.add({4, 2, KING, false, false, false, true}); // e1 to c1
        }
    }
    else {
        if (canCastle(board, BLACK, true)) {
            list.add({60, 62, KING, false, false, false, true}); // e8 to g8
        }
        if (canCastle(board, BLACK, false)) {
            list.add({60, 58, KING, false, false, false, true}); // e8 to c8
        }
    }
}