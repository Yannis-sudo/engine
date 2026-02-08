#include "../include/makemove.h"

// Führt einen Zug auf dem Board aus
void makemove(Board &board, const Move &move)
{
    if (board.pieces[WHITE][KING] == 0 || board.pieces[BLACK][KING] == 0)
    {
        std::cout << "KING BB == 0 in makemove line 7" << std::endl;
    }

    Color side = board.sideToMove;
    Color enemy = (side == WHITE ? BLACK : WHITE);

    int from = move.from;
    int to = move.to;
    int piece = move.piece;

    int capturedType = getPieceTypeOnSquare(board, to);
    if (capturedType == KING)
    {
        std::cout << "WARNING: Capturing a king at " << to << std::endl;
    }

    // --- Save history for undo ---
    HistoryEntry &h = board.history[board.historySize++];
    h.zobristKey = board.zobristKey;
    h.castlingRights = board.castlingRights;
    h.enPassantSquare = board.en_passant_square;
    h.halfmoveClock = board.halfmoveclock;
    h.move = move;
    h.capturedPiece = -1;

    // --- Update halfmove clock ---
    if (piece == PAWN || move.captured)
        board.halfmoveclock = 0;
    else
        board.halfmoveclock++;

    // --- Remove old en-passant hash ---
    if (board.en_passant_square != -1)
        board.zobristKey ^= zobristEnPassant[board.en_passant_square];

    board.en_passant_square = -1;

    // --- Remove piece from source square (hash + bitboard) ---
    board.pieces[side][piece] &= ~(1ULL << from);
    board.zobristKey ^= zobristPiece[side][piece][from];

    // --- Handle captures ---
    if (move.captured)
    {
        if (move.en_passant)
        {
            int capSq = (side == WHITE ? to - 8 : to + 8);
            board.pieces[enemy][PAWN] &= ~(1ULL << capSq);
            board.zobristKey ^= zobristPiece[enemy][PAWN][capSq];
            h.capturedPiece = PAWN;
        }
        else
        {
            int capturedType = getPieceTypeOnSquare(board, to);
            board.pieces[enemy][capturedType] &= ~(1ULL << to);
            board.zobristKey ^= zobristPiece[enemy][capturedType][to];
            h.capturedPiece = capturedType;
        }
    }

    // --- Promotion or normal move ---
    if (move.promotion)
    {
        board.pieces[side][move.promoteTo] |= (1ULL << to);
        board.zobristKey ^= zobristPiece[side][move.promoteTo][to];
    }
    else
    {
        board.pieces[side][piece] |= (1ULL << to);
        board.zobristKey ^= zobristPiece[side][piece][to];
    }

    // --- Castling rook movement ---
    if (move.castling)
    {
        if (side == WHITE)
        {
            if (to == 6) // White king-side
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 7);
                board.pieces[WHITE][ROOK] |= (1ULL << 5);

                board.zobristKey ^= zobristPiece[WHITE][ROOK][7];
                board.zobristKey ^= zobristPiece[WHITE][ROOK][5];
            }
            else if (to == 2) // White queen-side
            {
                board.pieces[WHITE][ROOK] &= ~(1ULL << 0);
                board.pieces[WHITE][ROOK] |= (1ULL << 3);

                board.zobristKey ^= zobristPiece[WHITE][ROOK][0];
                board.zobristKey ^= zobristPiece[WHITE][ROOK][3];
            }
        }
        else
        {
            if (to == 62) // Black king-side
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 63);
                board.pieces[BLACK][ROOK] |= (1ULL << 61);

                board.zobristKey ^= zobristPiece[BLACK][ROOK][63];
                board.zobristKey ^= zobristPiece[BLACK][ROOK][61];
            }
            else if (to == 58) // Black queen-side
            {
                board.pieces[BLACK][ROOK] &= ~(1ULL << 56);
                board.pieces[BLACK][ROOK] |= (1ULL << 59);

                board.zobristKey ^= zobristPiece[BLACK][ROOK][56];
                board.zobristKey ^= zobristPiece[BLACK][ROOK][59];
            }
        }
    }

    // --- Set new en-passant square (if double pawn push) ---
    if (piece == PAWN)
    {
        if (side == WHITE && from + 16 == to)
            board.en_passant_square = from + 8;
        else if (side == BLACK && from - 16 == to)
            board.en_passant_square = from - 8;

        if (board.en_passant_square != -1)
            board.zobristKey ^= zobristEnPassant[board.en_passant_square];
    }

    // --- Update castling rights (hash included) ---
    board.zobristKey ^= zobristCastling[board.castlingRights];
    updateCastlingRights(board, move);
    board.zobristKey ^= zobristCastling[board.castlingRights];

    // --- Switch side to move ---
    board.sideToMove = enemy;
    board.zobristKey ^= zobristSide;

    // --- Update occupancy bitboards ---
    board.updateOccupancy();

    if (board.pieces[WHITE][KING] == 0 || board.pieces[BLACK][KING] == 0)
    {
        std::cout << "KING BB == 0 in makemove line 139" << std::endl;
    }
}

void undomove(Board &board)
{
    if (board.pieces[WHITE][KING] == 0 || board.pieces[BLACK][KING] == 0)
    {
        std::cout << "KING BB == 0 in undomove line 149" << std::endl;
    }

    HistoryEntry &h = board.history[--board.historySize];

    Move move = h.move;
    Color enemy = board.sideToMove;
    Color side = (enemy == WHITE ? BLACK : WHITE);

    int from = move.from;
    int to = move.to;
    int piece = move.piece;

    // --- Restore simple board state ---
    board.sideToMove = side;
    board.zobristKey = h.zobristKey;
    board.castlingRights = h.castlingRights;
    board.en_passant_square = h.enPassantSquare;
    board.halfmoveclock = h.halfmoveClock;

    // --- Remove piece from target square ---
    if (move.promotion)
        board.pieces[side][move.promoteTo] &= ~(1ULL << to);
    else
        board.pieces[side][piece] &= ~(1ULL << to);

    // --- Put piece back on source square ---
    board.pieces[side][piece] |= (1ULL << from);

    // --- Restore captured piece ---
    if (h.capturedPiece != -1)
    {
        if (move.en_passant)
        {
            int capSq = (side == WHITE ? to - 8 : to + 8);
            board.pieces[enemy][PAWN] |= (1ULL << capSq);
        }
        else
        {
            board.pieces[enemy][h.capturedPiece] |= (1ULL << to);
        }
    }

    // --- Undo castling rook movement ---
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

    // --- Recalculate occupancy ---
    board.updateOccupancy();

    if (board.pieces[WHITE][KING] == 0 || board.pieces[BLACK][KING] == 0)
    {
        std::cout << "KING BB == 0 in undomove line 227" << std::endl;
    }
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