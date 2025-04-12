//
// Created by LIOR on 10/04/2025.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"
#include "Board.h"
#include <cmath>

class Queen : public Piece {
public:
    Queen(char letter) : Piece(letter) {
    }

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;
};

#endif //CHESS_QUEEN_H
