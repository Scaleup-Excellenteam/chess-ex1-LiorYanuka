//
// Created by LIOR on 09/04/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <vector>
#include <memory>
#include <string>
#include <array>

class Board {
protected:
    // Use a fixed-size 2D array instead of a vector of vectors
    // This is a different implementation but still a matrix representation
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> chessMatrix;
    
    // Helper method to check if coordinates are within board bounds
    bool isInBounds(int x, int y) const;

public:
    Board(const std::string& layout);
    Piece* getPiece(int x, int y) const;
    void movePiece(int fromX, int fromY, int toX, int toY);
    bool isInCheck(bool isWhite) const;
    void printBoard() const;
};


#endif //BOARD_H
