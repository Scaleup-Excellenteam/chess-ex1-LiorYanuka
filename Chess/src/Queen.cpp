//
// Created by LIOR on 10/04/2025.
//

#include "Queen.h"

bool Queen::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Queen moves like a rook or like a bishop
    if (fromX != toX && fromY != toY && abs(toX - fromX) != abs(toY - fromY)) {
        return false;
    }

    // Checks for clean path
    int stepX = (toX > fromX) ? 1 : (toX < fromX) ? -1 : 0;
    int stepY = (toY > fromY) ? 1 : (toY < fromY) ? -1 : 0;
    
    int x = fromX + stepX;
    int y = fromY + stepY;
    
    while (x != toX || y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }
    
    // Checks if the destination has our piece
    Piece* destPiece = board.getPiece(toX, toY);
    if (destPiece) {
        if ((isupper(_piece) && isupper(destPiece->getPiece())) ||
            (islower(_piece) && islower(destPiece->getPiece()))) {
            return false;
        }
    }
    
    return true;
} 