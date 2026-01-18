#pragma once

#include "./board.h"
#include "./bitboard.h"
#include "./movelist.h"

void makemove(Board &board, const Move &move);
void undomove(Board &board);

int getPieceTypeOnSquare(const Board &board, int sq);

inline void updateCastlingRights(Board &board, const Move &move) {
    const Color side = board.sideToMove;
    const bool isWhite = (side == WHITE);

    if (move.piece == KING) {
        board.castlingRights &= isWhite ? ~(WHITE_KINGSIDE | WHITE_QUEENSIDE) : ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);
    }

    if (move.piece == ROOK) {
        if (isWhite) {
            if (move.from == 0) board.castlingRights &= ~WHITE_QUEENSIDE; // a1
            if (move.from == 7) board.castlingRights &= ~WHITE_KINGSIDE;  // h1
        } else {
            if (move.from == 56) board.castlingRights &= ~BLACK_QUEENSIDE; // a8
            if (move.from == 63) board.castlingRights &= ~BLACK_KINGSIDE;  // h8
        }
    }

    // Berücksichtige die Erfassung von Figuren, um die Rochaderechte zu aktualisieren
    if (move.captured && !move.en_passant) {
        if (move.to == 0) board.castlingRights &= ~WHITE_QUEENSIDE; // a1
        if (move.to == 7) board.castlingRights &= ~WHITE_KINGSIDE;  // h1
        if (move.to == 56) board.castlingRights &= ~BLACK_QUEENSIDE; // a8
        if (move.to == 63) board.castlingRights &= ~BLACK_KINGSIDE;  // h8
    }
}
