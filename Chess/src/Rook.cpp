//
// Created by LIOR on 09/04/2025.
//

#include "Rook.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <utility>

// Constructor: sets the piece's symbol ('R' for white, 'r' for black)
// Also initializes hasMoved to false for castling rules
Rook::Rook(char symbol) : symbol(symbol), hasMoved(false) {}

// Returns the piece's symbol
char Rook::getPiece() const {
    return symbol;
}

// This is a different implementation approach than the original:
// 1. Uses a vector of direction vectors
// 2. Implements a path-tracing algorithm for checking moves
bool Rook::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Rooks can only move horizontally or vertically
    if (fromX != toX && fromY != toY) {
        return false;
    }
    
    // Define the four possible directions a rook can move
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},  // Up
        {1, 0},  // Right
        {0, -1}, // Down
        {-1, 0}  // Left
    };
    
    // Determine which direction we're moving
    int dx = 0, dy = 0;
    for (const auto& dir : directions) {
        if ((toX - fromX) * dir.first >= 0 && (toY - fromY) * dir.second >= 0) {
            if (fromX != toX) {
                dx = (toX > fromX) ? 1 : -1;
            }
            if (fromY != toY) {
                dy = (toY > fromY) ? 1 : -1;
            }
            break;
        }
    }
    
    // Check each square along the path to make sure it's clear
    int currentX = fromX + dx;
    int currentY = fromY + dy;
    
    while (currentX != toX || currentY != toY) {
        if (board.getPiece(currentX, currentY) != nullptr) {
            return false;  // Path is blocked
        }
        currentX += dx;
        currentY += dy;
    }
    
    // Check if destination has a piece of the same color
    Piece* destPiece = board.getPiece(toX, toY);
    if (destPiece) {
        // Cannot capture piece of same color
        // (uppercase = white, lowercase = black)
        bool srcIsWhite = isupper(symbol);
        bool destIsWhite = isupper(destPiece->getPiece());
        if (srcIsWhite == destIsWhite) {
            return false;
        }
    }
    
    // If we reach this point, the move is legal
    // Note: This would modify the object, but since isMoveLegal is const,
    // we can't set hasMoved here. The caller would need to call setMoved().
    return true;
}
