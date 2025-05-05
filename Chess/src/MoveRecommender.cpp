#include "MoveRecommender.h"
#include <algorithm>

MoveRecommender::MoveRecommender(Board &board, int maxDepth)
    : _board(board), _maxDepth(maxDepth) {
}

int MoveRecommender::getPieceValue(char piece) const {
    switch (toupper(piece)) {
        case 'K': return 1000;
        case 'Q': return 100;
        case 'R': return 50;
        case 'B': return 30;
        case 'N': return 30;
        case 'P': return 10;
        default: return 0;
    }
}

int MoveRecommender::evaluateMove(int fromX, int fromY, int toX, int toY, int depth, bool isWhiteTurn) {
    int score = 0;
    Piece *sourcePiece = _board.getPiece(fromX, fromY);
    Piece *targetPiece = _board.getPiece(toX, toY);

    // Moving +
    score += 1;

    // Capture +
    if (targetPiece) {
        score += getPieceValue(targetPiece->getPiece());
    }

    // Center control +
    if ((toX >= 3 && toX <= 4) && (toY >= 3 && toY <= 4)) {
        score += 5;
    }

    // Edge -
    if (toX == 0 || toX == 7 || toY == 0 || toY == 7) {
        score -= 2;
    }

    // Corner -
    if ((toX == 0 || toX == 7) && (toY == 0 || toY == 7)) {
        score -= 5;
    }

    return score;
}

void MoveRecommender::calculateMoves(bool isWhiteTurn, int numMoves) {
    _topMoves = PriorityQueue<Move>(numMoves);

    for (int fromX = 0; fromX < 8; fromX++) {
        for (int fromY = 0; fromY < 8; fromY++) {
            Piece *piece = _board.getPiece(fromX, fromY);
            if (!piece) continue;

            if ((isWhiteTurn && isupper(piece->getPiece())) ||
                (!isWhiteTurn && islower(piece->getPiece()))) {
                for (int toX = 0; toX < 8; toX++) {
                    for (int toY = 0; toY < 8; toY++) {
                        if (fromX == toX && fromY == toY) continue;

                        if (piece->isMoveLegal(fromX, fromY, toX, toY, _board)) {
                            int score = evaluateMove(fromX, fromY, toX, toY, 0, isWhiteTurn);
                            _topMoves.push(Move(fromX, fromY, toX, toY, score));
                        }
                    }
                }
            }
        }
    }
}

const PriorityQueue<Move> &MoveRecommender::getTopMoves() const {
    return _topMoves;
}

std::ostream &operator<<(std::ostream &os, const MoveRecommender &recommender) {
    PriorityQueue<Move> movesCopy = recommender.getTopMoves();

    // Print top 3 moves
    int count = 0;
    while (!movesCopy.isEmpty() && count < 3) {
        Move move = movesCopy.poll();
        os << "  " << (count + 1) << ". " << move.getNotation()
                << " (score: " << move.getScore() << ")" << std::endl;
        count++;
    }

    if (count == 0) {
        os << "  No legal moves available!" << std::endl;
    }

    return os;
}
