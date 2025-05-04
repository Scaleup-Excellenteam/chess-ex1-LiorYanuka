// Chess 
#include "Chess.h"
#include "Board.h"
#include "ChessExceptions.h"
#include <cctype>
#include <iostream>

int main() {
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	// string board = "RNBQKBNR################################################rnbqkbnr";
	Chess a(board);
	int codeResponse = 0;
	int currentPlayer = 1; // 1 for white (uppercase), 2 for black (lowercase)
	Board chessBoard(board); // Create a Board object
	string res = a.getInput();
	while (res != "exit") {
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is no piece at the source
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/
		{	// put your code here instead that code
			string move = res;
			try {
				// Checks if the input format is correct
				if (move.length() != 4) {
					throw IllegalMoveException("Invalid move format. Please use format like 'a2a4'.");
				}
				else {
					// Convert the input to the board
					int fromX = move[0] - 'a'; // Column
					int fromY = move[1] - '1'; // Row
					int toX = move[2] - 'a';
					int toY = move[3] - '1';

					// Gets which piece is it
					Piece *piece = chessBoard.getPiece(fromX, fromY);

					if (!piece) {
						throw IllegalMoveException("No piece at source position.");
					}
					// Checks if it's the enemy piece
					else if ((currentPlayer == 1 && islower(piece->getPiece())) ||
							(currentPlayer == 2 && isupper(piece->getPiece()))) {
						throw IllegalMoveException("Cannot move opponent's piece.");
					}
					else {
						// Checks if it's our piece
						Piece *dest = chessBoard.getPiece(toX, toY);
						if (dest &&
							((isupper(dest->getPiece()) && isupper(piece->getPiece())) ||
							(islower(dest->getPiece()) && islower(piece->getPiece())))) {
							throw IllegalMoveException("Cannot move to a position occupied by your own piece.");
						}
						// Checks if the move is illegal
						else if (!piece->isMoveLegal(fromX, fromY, toX, toY, chessBoard)) {
							throw IllegalMoveException("Illegal move for this piece.");
						}
						else {
							// Create a temp copy of the board
							Board tempBoard = chessBoard;
							tempBoard.movePiece(fromX, fromY, toX, toY);

							// Checks if there is check to us
							if (tempBoard.isInCheck(currentPlayer == 1)) {
								throw CheckmateException("This move would put you in check.");
							}
							else {
								chessBoard.movePiece(fromX, fromY, toX, toY);

								if (chessBoard.isInCheck(currentPlayer != 1)) {
									codeResponse = 41;
								}
								else {
									codeResponse = 42;
								}
								// Switch turn
								currentPlayer = (currentPlayer == 1) ? 2 : 1;
							}
						}
					}
				}
			}
			catch (const IllegalMoveException& e) {
				std::cerr << "Illegal move: " << e.what() << std::endl;
				if (move.length() != 4) {
					codeResponse = 21;
				} else {
					// Map exception to appropriate code response
					int fromX = move[0] - 'a';
					int fromY = move[1] - '1';
					Piece *piece = chessBoard.getPiece(fromX, fromY);
					if (!piece) {
						codeResponse = 11;
					} else if ((currentPlayer == 1 && islower(piece->getPiece())) ||
							(currentPlayer == 2 && isupper(piece->getPiece()))) {
						codeResponse = 12;
					} else {
						int toX = move[2] - 'a';
						int toY = move[3] - '1';
						Piece *dest = chessBoard.getPiece(toX, toY);
						if (dest && ((isupper(dest->getPiece()) && isupper(piece->getPiece())) ||
								(islower(dest->getPiece()) && islower(piece->getPiece())))) {
							codeResponse = 13;
						} else {
							codeResponse = 21;
						}
					}
				}
			}
			catch (const CheckmateException& e) {
				std::cerr << "Checkmate warning: " << e.what() << std::endl;
				codeResponse = 31;
			}
			catch (const std::exception& e) {
				std::cerr << "Error: " << e.what() << std::endl;
				codeResponse = 21;
			}
		}
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput();
	}

	cout << endl << "Exiting " << endl;
	return 0;
}
