#include "MoveRecommender.h"
#include <cctype>
#include <iostream>

// Gets piece value
int getPieceValue(char piece) {
    switch (std::toupper(piece)) {
        // King
        case 'K': return 1000;
        // Queen
        case 'Q': return 100;
        // Rook
        case 'R': return 50;
        // Bishop
        case 'B': return 30;
        // Knight
        case 'N': return 30;
        // Pawn
        case 'P': return 10;
        default: return 0;
    }
}

MoveRecommender::MoveRecommender(Board &board, int maxDepth)
    : _board(board), _maxDepth(maxDepth) {
}

int MoveRecommender::evaluateMove(int fromX, int fromY, int toX, int toY, int depth, bool isWhiteTurn) {
    Board tempBoard = _board;

    Piece *movingPiece = tempBoard.getPiece(fromX, fromY);
    if (!movingPiece) return 0;

    Piece *destPiece = tempBoard.getPiece(toX, toY);

    int score = 0;

    if (destPiece) {
        score += CAPTURE_SCORE;
    }

    tempBoard.movePiece(fromX, fromY, toX, toY);

    // Checks if threatened by a weaker piece or threatening a stronger piece
    if (isPieceThreatenedByWeaker(toX, toY, tempBoard, isWhiteTurn)) {
        score += UNDER_THREAT_BY_WEAKER;
    }

    if (isThreateningStrongerPiece(toX, toY, tempBoard, isWhiteTurn)) {
        score += THREATENS_STRONGER_PIECE;
    }

    if (depth >= _maxDepth) {
        return score;
    }

    // Evaluating by opponent`s best move subtracted by the best score from our score recursively
    if (depth < _maxDepth) {
        int opponentBestScore = getBestMoveScore(tempBoard, depth + 1, !isWhiteTurn);

        score -= opponentBestScore;

        if (depth + 2 <= _maxDepth) {
            int ourBestResponse = getBestMoveScore(tempBoard, depth + 2, isWhiteTurn);
            score += ourBestResponse;
        }
    }

    return score;
}

// Checks if threatened by a weaker piece
bool MoveRecommender::isPieceThreatenedByWeaker(int x, int y, Board &board, bool isWhite) {
    Piece *targetPiece = board.getPiece(x, y);
    if (!targetPiece) return false;

    int targetValue = getPieceValue(targetPiece->getPiece());

    for (int fromY = 0; fromY < 8; fromY++) {
        for (int fromX = 0; fromX < 8; fromX++) {
            Piece *piece = board.getPiece(fromX, fromY);

            if (!piece || (isWhite && isupper(piece->getPiece())) ||
                (!isWhite && islower(piece->getPiece()))) {
                continue;
            }

            if (piece->isMoveLegal(fromX, fromY, x, y, board)) {
                int attackerValue = getPieceValue(piece->getPiece());

                if (attackerValue < targetValue) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Checks if threatening a stronger piece
bool MoveRecommender::isThreateningStrongerPiece(int x, int y, Board &board, bool isWhite) {
    Piece *ourPiece = board.getPiece(x, y);
    if (!ourPiece) return false;

    int ourValue = getPieceValue(ourPiece->getPiece());

    for (int toY = 0; toY < 8; toY++) {
        for (int toX = 0; toX < 8; toX++) {
            if (!ourPiece->isMoveLegal(x, y, toX, toY, board)) {
                continue;
            }

            Piece *targetPiece = board.getPiece(toX, toY);

            if (!targetPiece || (isWhite && isupper(targetPiece->getPiece())) ||
                (!isWhite && islower(targetPiece->getPiece()))) {
                continue;
            }

            int targetValue = getPieceValue(targetPiece->getPiece());

            if (ourValue < targetValue) {
                return true;
            }
        }
    }

    return false;
}

int MoveRecommender::getBestMoveScore(Board &board, int depth, bool isWhiteTurn) {
    PriorityQueue<Move> moves(1);

    // All possible moves at this depth
    for (int fromY = 0; fromY < 8; fromY++) {
        for (int fromX = 0; fromX < 8; fromX++) {
            Piece *piece = board.getPiece(fromX, fromY);

            // No empty spots or opponent`s
            if (!piece || (isWhiteTurn && islower(piece->getPiece())) ||
                (!isWhiteTurn && isupper(piece->getPiece()))) {
                continue;
            }

            for (int toY = 0; toY < 8; toY++) {
                for (int toX = 0; toX < 8; toX++) {
                    if (!piece->isMoveLegal(fromX, fromY, toX, toY, board)) {
                        continue;
                    }

                    // Skips moves that would capture our own pieces
                    Piece *destPiece = board.getPiece(toX, toY);
                    if (destPiece &&
                        ((isupper(destPiece->getPiece()) && isupper(piece->getPiece())) ||
                         (islower(destPiece->getPiece()) && islower(piece->getPiece())))) {
                        continue;
                    }

                    Board tempBoard = board;
                    tempBoard.movePiece(fromX, fromY, toX, toY);
                    if (tempBoard.isInCheck(isWhiteTurn)) {
                        continue;
                    }

                    int score = evaluateMove(fromX, fromY, toX, toY, depth, isWhiteTurn);

                    moves.push(Move(fromX, fromY, toX, toY, score));
                }
            }
        }
    }

    if (moves.isEmpty()) {
        return 0;
    }

    return moves.peek().getScore();
}

void MoveRecommender::calculateMoves(bool isWhiteTurn, int numMoves) {
    _topMoves = PriorityQueue<Move>(numMoves);

    // All possible moves for this player
    for (int fromY = 0; fromY < 8; fromY++) {
        for (int fromX = 0; fromX < 8; fromX++) {
            Piece *piece = _board.getPiece(fromX, fromY);

            // No empty spots or opponent`s
            if (!piece || (isWhiteTurn && islower(piece->getPiece())) ||
                (!isWhiteTurn && isupper(piece->getPiece()))) {
                continue;
            }

            for (int toY = 0; toY < 8; toY++) {
                for (int toX = 0; toX < 8; toX++) {
                    // Skip invalid moves
                    if (!piece->isMoveLegal(fromX, fromY, toX, toY, _board)) {
                        continue;
                    }

                    // Skips moves that would capture our own pieces
                    Piece *destPiece = _board.getPiece(toX, toY);
                    if (destPiece &&
                        ((isupper(destPiece->getPiece()) && isupper(piece->getPiece())) ||
                         (islower(destPiece->getPiece()) && islower(piece->getPiece())))) {
                        continue;
                    }

                    Board tempBoard = _board;
                    tempBoard.movePiece(fromX, fromY, toX, toY);
                    if (tempBoard.isInCheck(isWhiteTurn)) {
                        continue;
                    }

                    int score = evaluateMove(fromX, fromY, toX, toY, 0, isWhiteTurn);

                    _topMoves.push(Move(fromX, fromY, toX, toY, score));
                }
            }
        }
    }
}

const PriorityQueue<Move> &MoveRecommender::getTopMoves() const {
    return _topMoves;
}

std::ostream &operator<<(std::ostream &os, const MoveRecommender &recommender) {
    os << "Top recommended moves:" << std::endl;

    PriorityQueue<Move> movesCopy = recommender.getTopMoves();

    // Print top 3 moves
    int count = 0;
    while (!movesCopy.isEmpty() && count < 3) {
        Move move = movesCopy.poll();
        os << (count + 1) << ". " << move.getNotation()
                << " (score: " << move.getScore() << ")" << std::endl;
        count++;
    }

    return os;
}
