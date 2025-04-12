//
// Created by LIOR on 09/04/2025.
//

#include "Rook.h"


bool Rook::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const {
    // Rook moves straight in one direction
    if (fromX != toX && fromY != toY) {
        return false;
    }

    // Checks if the path is clean
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
    Piece *destPiece = board.getPiece(toX, toY);
    if (destPiece) {
        if ((isupper(_piece) && isupper(destPiece->getPiece())) ||
            (islower(_piece) && islower(destPiece->getPiece()))) {
            return false;
        }
    }

    return true;
}
