//
// Created by LIOR on 10/04/2025.
//

#include "King.h"

bool King::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const {
    // King can move one square in any direction
    int dx = abs(toX - fromX);
    int dy = abs(toY - fromY);

    // Checks if the move is legal
    if (dx > 1 || dy > 1) {
        return false;
    }

    // Checks if we don't have our piece in the destination
    Piece *destPiece = board.getPiece(toX, toY);
    if (destPiece) {
        if ((isupper(_piece) && isupper(destPiece->getPiece())) ||
            (islower(_piece) && islower(destPiece->getPiece()))) {
            return false;
        }
    }

    return true;
}
