//
// Created by LIOR on 09/04/2025.
//

#include "Knight.h"

bool Knight::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const {
    // Knight moves in an L-shape: 2 to one direction and 1 to the other
    int dx = abs(toX - fromX);
    int dy = abs(toY - fromY);

    // Checks if the move is legal
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
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
