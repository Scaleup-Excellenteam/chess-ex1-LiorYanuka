//
// Created by LIOR
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include <cctype> // For isupper function

// Knight class that inherits from Piece
class Knight : public Piece {
protected:
    char letter; // Stores the piece letter (upper for white, lower for black)

public:
    // Constructor for Knight
    Knight(char letter);

    // Returns the letter of the piece ('N' or 'n')
    char getPiece() const override;

    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const override;
};


#endif //KNIGHT_H 