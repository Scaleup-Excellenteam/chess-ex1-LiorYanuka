//
// Created by LIOR on 10/04/2025.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"
#include "Board.h"
#include <cmath>

class Pawn : public Piece {
protected:
    bool hasMoved; // Checks if already moved, if so can only move once, if not can move twice

public:
    Pawn(char letter) : Piece(letter), hasMoved(false) {}
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    void setMoved() { hasMoved = true; }
    bool getHasMoved() const { return hasMoved; }
};

#endif //CHESS_PAWN_H 