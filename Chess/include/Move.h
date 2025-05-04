#pragma once

#include <string>

using namespace std;

// This class will help us encapsulate the information about a move
class Move {
private:
    int _fromX;
    int _fromY;
    int _toX;
    int _toY;
    int _score;
    std::string _notation;

public:
    Move(int fromX, int fromY, int toX, int toY, int score = 0):
    _fromX(fromX), _fromY(fromY), _toX(toX), _toY(toY), _score(score) {
        // Generates the notation
        _notation = static_cast<char>('a' + fromX);
        _notation += static_cast<char>('1' + fromY);
        _notation += static_cast<char>('a' + toX);
        _notation += static_cast<char>('1' + toY);
    }

    // Simple getters
    int getFromX() const { return _fromX; }
    int getFromY() const { return _fromY; }
    int getToX() const { return _toX; }
    int getToY() const { return _toY; }
    int getScore() const { return _score; }
    void setScore(int score) { _score = score; }
    const std::string& getNotation() const { return _notation; }

    // To use with my PriorityQueue
    int operator-(const Move& other) const {
        return other._score - _score;
    }
}; 