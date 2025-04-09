//
// Created by LIOR on 09/04/2025.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

// Rook class that inherits from Piece
class Rook : public Piece {
private:
    char symbol; // Changed from "letter" to "symbol"
    bool hasMoved; // Added to track if rook has moved (for castling)

public:
    // Constructor for rook
    Rook(char symbol);

    // Returns the letter of the piece ('R' or 'r')
    char getPiece() const override;

    // Check if a move is legal for this rook
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    
    // Mark that the rook has moved (for castling)
    void setMoved() { hasMoved = true; }
    
    // Check if the rook has moved (for castling)
    bool getHasMoved() const { return hasMoved; }
};


#endif //ROOK_H
