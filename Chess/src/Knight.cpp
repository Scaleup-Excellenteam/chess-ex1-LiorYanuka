//
// Created by LIOR
//

#include "Knight.h"
#include "Board.h"
#include <cmath>

// Constructor: sets the piece's symbol ('N' for white, 'n' for black)
Knight::Knight(char letter) : letter(letter) {}

// Returns the piece's symbol
char Knight::getPiece() const {
    return letter;
}

bool Knight::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Knight moves in an L shape: 2 squares in one direction and 1 square perpendicular
    int dx = abs(toX - fromX);
    int dy = abs(toY - fromY);
    
    if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1)) {
        // Check if destination has a piece of the same color
        Piece* dest = board.getPiece(toX, toY);
        return dest == nullptr || (isupper(dest->getPiece()) != isupper(this->getPiece()));
    }
    
    return false;
} 