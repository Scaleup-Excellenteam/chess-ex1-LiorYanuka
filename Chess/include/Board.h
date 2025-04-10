//
// Created by LIOR on 06/04/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <memory>
#include <string>
#include <array>

class Board {
protected:
    // Matrix for saving the board with Piece class
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> chessMatrix;

    // Checks if we are in bounds
    bool isInBounds(int x, int y) const;

public:
    // Constructor
    Board(const std::string &layout);

    // Gets a pointer to the piece
    Piece *getPiece(int x, int y) const;

    // Move the piece from (x1,y1) to (x2,y2)
    void movePiece(int fromX, int fromY, int toX, int toY);

    // Checks if there is a check to the current player
    bool isInCheck(bool isWhite) const;
};


#endif //BOARD_H
