#include <iostream>
#include "../include/initstartposition.h"
#include "../generatemoves/include/generatemoves.h"
#include <limits>

#include "../tables/include/attacks.h"
#include "../tables/include/masks.h"
#include "../tables/include/lookup.h"
#include "../global/include/generatemovesvar.h"
#include "../minimax/include/minimax.h"
#include "../include/bestmove.h"
#include "../evaluate/include/ptstables.h"
#include <string>
#include <sstream>

using namespace std;

string current_fen = "startpos";
Board currentBoard;
bool maximizing;
int depht = 5;

Board parse_fen(const std::string &fen)
{
    Board b;

    // 1. Bitboards leeren
    for (int c = 0; c < 2; c++)
        for (int p = 0; p < 6; p++)
            b.pieces[c][p] = 0ULL;

    b.occupied[WHITE] = 0ULL;
    b.occupied[BLACK] = 0ULL;
    b.occupiedAll = 0ULL;

    // 2. FEN in Teile splitten
    std::istringstream ss(fen);
    std::string boardPart, side, castling, enpassant;
    ss >> boardPart >> side >> castling >> enpassant >> b.halfmoveclock >> b.fullmoveNumber;

    // 3. Figuren setzen
    int rank = 7;
    int file = 0;

    for (char c : boardPart)
    {
        if (c == '/')
        {
            rank--;
            file = 0;
            continue;
        }

        if (isdigit(c))
        {
            file += c - '0';
            continue;
        }

        int sq = rank * 8 + file;

        switch (c)
        {
        case 'P':
            b.pieces[WHITE][PAWN] |= 1ULL << sq;
            break;
        case 'N':
            b.pieces[WHITE][KNIGHT] |= 1ULL << sq;
            break;
        case 'B':
            b.pieces[WHITE][BISHOP] |= 1ULL << sq;
            break;
        case 'R':
            b.pieces[WHITE][ROOK] |= 1ULL << sq;
            break;
        case 'Q':
            b.pieces[WHITE][QUEEN] |= 1ULL << sq;
            break;
        case 'K':
            b.pieces[WHITE][KING] |= 1ULL << sq;
            break;

        case 'p':
            b.pieces[BLACK][PAWN] |= 1ULL << sq;
            break;
        case 'n':
            b.pieces[BLACK][KNIGHT] |= 1ULL << sq;
            break;
        case 'b':
            b.pieces[BLACK][BISHOP] |= 1ULL << sq;
            break;
        case 'r':
            b.pieces[BLACK][ROOK] |= 1ULL << sq;
            break;
        case 'q':
            b.pieces[BLACK][QUEEN] |= 1ULL << sq;
            break;
        case 'k':
            b.pieces[BLACK][KING] |= 1ULL << sq;
            break;
        }

        file++;
    }

    // 4. Side to move
    b.sideToMove = (side == "w" ? WHITE : BLACK);
    if (side == "w")
    {
        maximizing = true;
    }
    else
    {
        maximizing = false;
    }

    // 5. Castling rights
    b.wks = castling.find('K') != std::string::npos;
    b.wqs = castling.find('Q') != std::string::npos;
    b.bks = castling.find('k') != std::string::npos;
    b.bqs = castling.find('q') != std::string::npos;

    // 6. En passant square
    if (enpassant == "-")
    {
        b.en_passant_square = -1;
    }
    else
    {
        int file = enpassant[0] - 'a';
        int rank = enpassant[1] - '1';
        b.en_passant_square = rank * 8 + file;
    }

    // 7. Occupancy aktualisieren
    b.updateOccupancy();

    return b;
}

void uci_loop()
{
    string line;
    while (getline(cin, line))
    {
        if (line == "uci")
        {
            cout << "id name ChessEngine\n";
            cout << "id author Yannis Benz\n";
            cout << "uciok\n"; // vorher: "ucion\n"
        }
        else if (line == "isready")
        {
            cout << "readyok\n";
        }
        else if (line.rfind("position", 0) == 0)
        {
            string arg = line.substr(9);
            // Erwartet: "startpos" oder "fen <fenstring> [moves ...]"
            currentBoard = parse_fen(arg);
        }
        else if (line.rfind("depth", 0) == 0 || line.rfind("depht", 0) == 0)
        {
            // akzeptiere beide Schreibweisen, setze interne Variable
            string depthStr = (line.rfind("depth", 0) == 0) ? line.substr(6) : line.substr(6);
            int depth2 = stoi(depthStr);
            depht = depth2;
        }
        else if (line.rfind("go", 0) == 0)
        {
            // simple handling: benutze den gesetzten depht (oder standard) und berechne bestmove
            auto best = bestmove(currentBoard, maximizing, depht);
            cout << "bestmove " << best << "\n";
        }
        else if (line.rfind("bestmove", 0) == 0)
        {
            auto best = bestmove(currentBoard, maximizing, depht);
            cout << best << endl;
        }
        else if (line.rfind("besteval", 0) == 0)
        {
            int eval = minimax(currentBoard, depht, -1000000, 1000000, true);
            cout << "besteval " << eval << endl;
        }
        else if (line == "quit")
        {
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    // Init Tables
    // Generate Moves Table
    initAttackTable();
    initMasks();
    initRelevantBits();
    initBishopRookTables();
    initPawnAttacks();

    // Evaluate tables
    initPSTTables();

    uci_loop();

    return 0;
}
