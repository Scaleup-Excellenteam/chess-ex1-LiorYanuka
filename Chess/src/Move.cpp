#include "Move.h"

Move::Move(int fromX, int fromY, int toX, int toY, int score) : _fromX(fromX), _fromY(fromY), _toX(toX), _toY(toY),
                                                                _score(score) {
    // Generates the notation
    _notation = static_cast<char>('a' + fromX);
    _notation += static_cast<char>('1' + fromY);
    _notation += static_cast<char>('a' + toX);
    _notation += static_cast<char>('1' + toY);
}

int Move::getFromX() const {
    return _fromX;
}

int Move::getFromY() const {
    return _fromY;
}

int Move::getToX() const {
    return _toX;
}

int Move::getToY() const {
    return _toY;
}

int Move::getScore() const {
    return _score;
}

void Move::setScore(int score) {
    _score = score;
}

const string &Move::getNotation() const {
    return _notation;
}

int Move::operator-(const Move &other) const {
    return _score - other._score;
}
