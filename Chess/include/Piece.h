//
// Created by LIOR on 07/04/2025.
//

#ifndef PIECE_H
#define PIECE_H

class Board;

// Class for all pieces
class Piece {
protected:
    char _piece; // Store the piece character

public:
    // Constructor
    Piece(char piece) : _piece(piece) {
    }

    // Checks if the move is legal
    virtual bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board &board) const = 0;

    // Returns the piece letter
    virtual char getPiece() const { return _piece; }

    // Destructor
    virtual ~Piece() = default;
};


#endif //PIECE_H
