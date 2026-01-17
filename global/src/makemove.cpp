#include "../include/makemove.h"

// Führt einen Zug auf dem Board aus
void makemove(Board &board, const Move &move)
{
    Color side = board.sideToMove;
    Color enemy = (side == WHITE ? BLACK : WHITE);

    const int from = move.from;
    const int to = move.to;
    const int piece = move.piece;

    // Save history
    HistoryEntry &h = board.history[board.historySize++];
    h.zobristKey = board.zobristKey;
    h.castlingRights = board.castlingRights;
    h.enPassantSquare = board.en_passant_square;
    h.halfmoveClock = board.halfmoveclock;
    h.move = move;
    h.capturedPiece = -1;

    // Half move counter
    if (piece == PAWN || move.captured)
        board.halfmoveclock = 0;
    else
        board.halfmoveclock++;

    // Delete en passant
    board.en_passant_square = -1;

    // Remove piece from source square
    board.pieces[side][piece] &= ~(1ULL << from);

    // Capture
    if (move.captured)
    {
        if (move.en_passant)
        {
            const int capSq = (side == WHITE ? to - 8 : to + 8);
            board.pieces[enemy][PAWN] &= ~(1ULL << capSq);
            h.capturedPiece = PAWN;
        }
        else
        {
            const int capturedType = getPieceTypeOnSquare(board, to);
            board.pieces[enemy][capturedType] &= ~(1ULL << to);
            h.capturedPiece = capturedType;
        }
    }

    // Promotion
    if (move.promotion)
    {
        board.pieces[side][move.promoteTo] |= (1ULL << to);
    }
    else
    {
        board.pieces[side][piece] |= (1ULL << to);
    }

    // Catling
    if (move.castling)
    {
        if (side == WHITE)
        {
            if (to == 6)
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 7);
                board.pieces[WHITE][ROOK] |= (1ULL << 5);
            }
            else if (to == 2)
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 0);
                board.pieces[WHITE][ROOK] |= (1ULL << 3);
            }
        }
        else
        {
            if (to == 62)
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 63);
                board.pieces[BLACK][ROOK] |= (1ULL << 61);
            }
            else if (to == 58)
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 56);
                board.pieces[BLACK][ROOK] |= (1ULL << 59);
            }
        }
    }

    // Set en passant
    if (piece == PAWN)
    {
        if (side == WHITE && from + 16 == to)
        {
            board.en_passant_square = from + 8;
        }
        else if (side == BLACK && from - 16 == to)
        {
            board.en_passant_square = from - 8;
        }
    }

    // switch sides
    board.sideToMove = enemy;
    // Update occupancy
    board.updateOccupancy();
}

void undomove(Board &board)
{
    HistoryEntry &h = board.history[--board.historySize];

    const Move move = h.move;
    const Color enemy = board.sideToMove;
    const Color side = (enemy == WHITE ? BLACK : WHITE);

    const int from = move.from;
    const int to = move.to;
    const int piece = move.piece;

    // Reswitc side
    board.sideToMove = side;
    board.zobristKey = h.zobristKey;
    board.castlingRights = h.castlingRights;
    board.en_passant_square = h.enPassantSquare;
    board.halfmoveclock = h.halfmoveClock;

    if (move.promotion)
    {
        board.pieces[side][move.promoteTo] &= ~(1ULL << to);
    }
    else
    {
        board.pieces[side][piece] &= ~(1ULL << to);
    }

    board.pieces[side][piece] |= (1ULL << from);

    if (h.capturedPiece != -1)
    {
        if (move.en_passant)
        {
            const int capSq = (side == WHITE ? to - 8 : to + 8);
            board.pieces[enemy][PAWN] |= (1ULL << capSq);
        }
        else
        {
            board.pieces[enemy][h.capturedPiece] |= (1ULL << to);
        }
    }

    // Undo catling
    if (move.castling)
    {
        if (side == WHITE)
        {
            if (to == 6)
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 5);
                board.pieces[WHITE][ROOK] |= (1ULL << 7);
            }
            else if (to == 2)
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 3);
                board.pieces[WHITE][ROOK] |= (1ULL << 0);
            }
        }
        else
        {
            if (to == 62)
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 61);
                board.pieces[BLACK][ROOK] |= (1ULL << 63);
            }
            else if (to == 58)
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 59);
                board.pieces[BLACK][ROOK] |= (1ULL << 56);
            }
        }
    }
    board.updateOccupancy();
}

int getPieceTypeOnSquare(const Board &board, int sq)
{
    Bitboard bb = 1ULL << sq;

    if (board.pieces[WHITE][PAWN] & bb)
        return PAWN;
    if (board.pieces[WHITE][ROOK] & bb)
        return ROOK;
    if (board.pieces[WHITE][KNIGHT] & bb)
        return KNIGHT;
    if (board.pieces[WHITE][BISHOP] & bb)
        return BISHOP;
    if (board.pieces[WHITE][QUEEN] & bb)
        return QUEEN;
    if (board.pieces[WHITE][KING] & bb)
        return KING;

    if (board.pieces[BLACK][PAWN] & bb)
        return PAWN;
    if (board.pieces[BLACK][ROOK] & bb)
        return ROOK;
    if (board.pieces[BLACK][KNIGHT] & bb)
        return KNIGHT;
    if (board.pieces[BLACK][BISHOP] & bb)
        return BISHOP;
    if (board.pieces[BLACK][QUEEN] & bb)
        return QUEEN;
    if (board.pieces[BLACK][KING] & bb)
        return KING;

    return -1; // kein Stück gefunden
}