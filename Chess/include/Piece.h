//
// Created by LIOR on 09/04/2025.
//

#ifndef PIECE_H
#define PIECE_H

class Board;

// Class for all pieces
class Piece {

public:
    virtual bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const = 0;

    // Returns the piece letter
    virtual char getPiece() const = 0;

    // Destructor
    virtual ~Piece() = default;
};


#endif //PIECE_H
