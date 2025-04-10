//
// Created by LIOR on 06/04/2025.
//

#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"

#include <iostream>
#include <string>
#include <cctype>


bool Board::isInBounds(int x, int y) const {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

Board::Board(const std::string &layout) {
    // Initialize all positions in the matrix to nullptr
    for (auto &row: chessMatrix) {
        for (auto &cell: row) {
            cell = nullptr;
        }
    }

    // Placing pieces according to the string, the switch takes each letter and adds it
    for (int i = 0; i < 64 && i < layout.length(); ++i) {
        char c = layout[i];
        int row = i / 8;
        int col = i % 8;


        switch (c) {
            case 'R':
                chessMatrix[row][col] = std::make_shared<Rook>('R');
                break;
            case 'r':
                chessMatrix[row][col] = std::make_shared<Rook>('r');
                break;
            case 'N':
                chessMatrix[row][col] = std::make_shared<Knight>('N');
                break;
            case 'n':
                chessMatrix[row][col] = std::make_shared<Knight>('n');
                break;
            case 'K':
                chessMatrix[row][col] = std::make_shared<King>('K');
                break;
            case 'k':
                chessMatrix[row][col] = std::make_shared<King>('k');
                break;
            case 'B':
                chessMatrix[row][col] = std::make_shared<Bishop>('B');
                break;
            case 'b':
                chessMatrix[row][col] = std::make_shared<Bishop>('b');
                break;
            case 'Q':
                chessMatrix[row][col] = std::make_shared<Queen>('Q');
                break;
            case 'q':
                chessMatrix[row][col] = std::make_shared<Queen>('q');
                break;
            case 'P':
                chessMatrix[row][col] = std::make_shared<Pawn>('P');
                break;
            case 'p':
                chessMatrix[row][col] = std::make_shared<Pawn>('p');
                break;
            default:
                chessMatrix[row][col] = nullptr; // Empty square or unsupported piece
        }
    }
}


Piece *Board::getPiece(int x, int y) const {
    if (!isInBounds(x, y))
        return nullptr;

    return chessMatrix[x][y].get();
}

void Board::movePiece(int fromX, int fromY, int toX, int toY) {
    // If the piece is a pawn, mark it as moved
    Piece *piece = getPiece(fromX, fromY);
    if (piece && (piece->getPiece() == 'P' || piece->getPiece() == 'p')) {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn) {
            pawn->setMoved();
        }
    }

    chessMatrix[toX][toY] = chessMatrix[fromX][fromY];
    chessMatrix[fromX][fromY] = nullptr;
}

bool Board::isInCheck(bool isWhite) const {
    char kingSymbol = isWhite ? 'K' : 'k';

    int kingX = -1, kingY = -1;

    // Locates the king
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece *p = getPiece(x, y);
            if (p && p->getPiece() == kingSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }

    if (kingX == -1) return false; // The king wasn't found

    // Checks if enemy can move to king
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece *p = getPiece(x, y);
            if (p && isupper(p->getPiece()) != isWhite) {
                // Opponent's piece
                if (p->isMoveLegal(x, y, kingX, kingY, *this)) {
                    return true; // Enemy can cause check
                }
            }
        }
    }

    return false; // No threats to king
}
