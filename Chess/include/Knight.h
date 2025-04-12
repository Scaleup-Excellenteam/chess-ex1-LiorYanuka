//
// Created by LIOR on 09/04/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"
#include <cmath>


class Knight : public Piece {
public:
    Knight(char letter) : Piece(letter) {
    }

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;
};

#endif //KNIGHT_H
