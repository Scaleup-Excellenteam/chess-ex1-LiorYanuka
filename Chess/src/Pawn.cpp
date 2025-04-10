//
// Created by LIOR on 10/04/2025.
//

#include "Pawn.h"

bool Pawn::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const {
    // We need to check which color`s piece is it to know what direction it can move
    // X=0 is white, X=7 is black
    int direction = isupper(_piece) ? 1 : -1; // White pawns move down, black pawns move up


    if (fromY == toY) {
        if (board.getPiece(toX, toY) != nullptr) {
            return false;
        }

        // Checks if moving one square
        if (toX == fromX + direction) {
            return true;
        }

        // Checks if moving two squares on the first move
        if (!hasMoved && toX == fromX + 2 * direction) {
            // Checks if the square between is empty
            if (board.getPiece(fromX + direction, fromY) == nullptr) {
                return true;
            }
        }
    }
    // Pawns capture diagonally
    else if (abs(toY - fromY) == 1 && toX == fromX + direction) {
        Piece *destPiece = board.getPiece(toX, toY);
        if (destPiece) {
            if ((isupper(_piece) && islower(destPiece->getPiece())) ||
                (islower(_piece) && isupper(destPiece->getPiece()))) {
                return true;
            }
        }
    }

    return false;
}
