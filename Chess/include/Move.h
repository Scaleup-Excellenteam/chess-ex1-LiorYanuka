#pragma once

#include <string>

using namespace std;

// This class will help us with the information about each move
class Move {
private:
    int _fromX;
    int _fromY;
    int _toX;
    int _toY;
    int _score;
    string _notation;

public:
    // Constructor
    Move(int fromX, int fromY, int toX, int toY, int score = 0);

    // Simple getters
    int getFromX() const;

    int getFromY() const;

    int getToX() const;

    int getToY() const;

    int getScore() const;

    void setScore(int score);

    const string &getNotation() const;

    // To use with my PriorityQueue
    int operator-(const Move &other) const;
};
