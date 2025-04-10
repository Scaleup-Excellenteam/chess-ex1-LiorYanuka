//
// Created by LIOR on 09/04/2025.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"
#include <cmath>

class Rook : public Piece {
protected:
    bool hasMoved; // To do castling

public:
    Rook(char letter) : Piece(letter), hasMoved(false) {
    }

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;

    void setMoved() { hasMoved = true; }

    bool getHasMoved() const { return hasMoved; }
};

#endif //ROOK_H
