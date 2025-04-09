//
// Created by LIOR on 09/04/2025.
//

#include "Board.h"

#include <iostream>
#include <string>
#include <cctype>

#include "Rook.h"
#include "Knight.h"
// #include "King.h"
// #include "Bishop.h"
// #include "Queen.h"

// Helper method to check if coordinates are within board bounds
bool Board::isInBounds(int x, int y) const {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// Constructor: builds the board from a 64-character layout string
Board::Board(const std::string& layout) {
    // Initialize all positions in the matrix to nullptr
    for (auto& row : chessMatrix) {
        for (auto& cell : row) {
            cell = nullptr;
        }
    }

    // Loop through the layout string and place pieces
    for (int i = 0; i < 64 && i < layout.length(); ++i) {
        char c = layout[i];
        int row = i / 8; // Row index (0–7 from top to bottom)
        int col = i % 8; // Column index (0–7 from left to right)

        // Switch to place correct piece depending on the character
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
            /*
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
            */
            default:
                chessMatrix[row][col] = nullptr; // Empty square or unsupported piece
        }
    }
}

// Returns a pointer to the piece at the given coordinates
Piece* Board::getPiece(int x, int y) const {
    if (!isInBounds(x, y))
        return nullptr;  // Out of bounds
    
    return chessMatrix[x][y].get();
}

// Moves a piece from (fromX, fromY) to (toX, toY)
void Board::movePiece(int fromX, int fromY, int toX, int toY) {
    chessMatrix[toX][toY] = chessMatrix[fromX][fromY];   // Move the piece
    chessMatrix[fromX][fromY] = nullptr;                 // Empty the source square
}

// Print the board for debugging
void Board::printBoard() const {
    std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 8; j++) {
            Piece* p = getPiece(i, j);
            if (p) {
                std::cout << p->getPiece() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

// Checks if the king of the given player is currently in check
bool Board::isInCheck(bool isWhite) const {
    // This is temporarily commented out until King class is implemented
    /*
    char kingSymbol = isWhite ? 'K' : 'k'; // Use correct symbol for the player's king

    int kingX = -1, kingY = -1;

    // First, locate the king on the board
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && p->getPiece() == kingSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    if (kingX == -1) return false; /// King not found

    // Now, check if any enemy piece can legally move to the king's position
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && isupper(p->getPiece()) != isWhite) { // Opponent's piece
                if (p->isMoveLegal(x, y, kingX, kingY, *this)) {
                    return true; // Enemy piece can attack the king → check
                }
            }
        }
    }
    */
    return false; // No threats found → not in check
}
