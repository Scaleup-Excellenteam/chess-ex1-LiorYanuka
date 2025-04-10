//
// Created by LIOR on 10/04/2025.
//

#include "Bishop.h"

bool Bishop::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const {
    // Bishop moves diagonally
    if (abs(toX - fromX) != abs(toY - fromY)) {
        return false;
    }

    // Check if there are any pieces in the path
    int stepX = (toX > fromX) ? 1 : -1;
    int stepY = (toY > fromY) ? 1 : -1;

    int x = fromX + stepX;
    int y = fromY + stepY;

    while (x != toX && y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }

    // Check if the destination square is occupied by a piece of the same color
    Piece *destPiece = board.getPiece(toX, toY);
    if (destPiece) {
        if ((isupper(_piece) && isupper(destPiece->getPiece())) ||
            (islower(_piece) && islower(destPiece->getPiece()))) {
            return false;
        }
    }

    return true;
}
