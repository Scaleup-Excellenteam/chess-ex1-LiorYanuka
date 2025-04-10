//
// Created by LIOR on 10/04/2025.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"
#include "Board.h"
#include <cmath>

class Bishop : public Piece {
public:
    Bishop(char letter) : Piece(letter) {
    }

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;
};

#endif //CHESS_BISHOP_H
