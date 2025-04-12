//
// Created by LIOR on 10/04/2025.
//

#include "Piece.h"
#include "Board.h"
#include <stdlib.h>
#include <ctype.h>


class King : public Piece {
public:
    King(char piece) : Piece(piece) {
    }

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;
};
