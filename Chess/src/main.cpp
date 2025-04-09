// Chess 
#include "Chess.h"
#include "Board.h"
#include "Rook.h"  // Add include for Rook class
#include <cctype>  // For isupper/islower
#include <iostream>

int main()
{
	// string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	string board = "RN####NR################################################rn####nr";
	Chess a(board);
	int codeResponse = 0;
	int currentPlayer = 1;  // 1 for white (uppercase), 2 for black (lowercase)
	Board chessBoard(board);  // Create a Board object
	string res = a.getInput();
	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		{ // put your code here instead that code
			string move = res;  // Save the input move string (e.g. "e2e4")
			
			if (move.length() != 4) {
				codeResponse = 21; // Invalid move format, must be exactly 4 characters
			} else {
				// Convert chess notation (e.g. "e2") to board coordinates
				int fromX = move[0] - 'a'; // Column: 'a'-'h' → 0-7
				int fromY = move[1] - '1'; // Row: '1'-'8' → 0-7 (bottom to top)
				int toX   = move[2] - 'a';
				int toY   = move[3] - '1';
				
				// Get the piece from the source square
				Piece* piece = chessBoard.getPiece(fromX, fromY);
				
				if (!piece) {
					// No piece at the source location
					codeResponse = 11;
				}
				// Check if the piece belongs to the opponent
				else if ((currentPlayer == 1 && islower(piece->getPiece())) ||
						 (currentPlayer == 2 && isupper(piece->getPiece()))) {
					codeResponse = 12;
				}
				else {
					// Check if destination square contains a piece of the same player
					Piece* dest = chessBoard.getPiece(toX, toY);
					if (dest &&
						((isupper(dest->getPiece()) && isupper(piece->getPiece())) ||
						 (islower(dest->getPiece()) && islower(piece->getPiece())))) {
						codeResponse = 13; // Illegal move: destination has your own piece
					}
					// Check if the move is illegal for that specific piece
					else if (!piece->isMoveLegal(fromX, fromY, toX, toY, chessBoard)) {
						codeResponse = 21; // Illegal move by that piece type
					}
					else {
						// Create a temporary copy of the board to simulate the move
						Board tempBoard = chessBoard; // Temporary board copy
						tempBoard.movePiece(fromX, fromY, toX, toY);
						
						// Check if the move would put the current player's king in check
						if (tempBoard.isInCheck(currentPlayer == 1)) {
							codeResponse = 31; // Move causes self-check — not allowed
						} else {
							// Move is legal and doesn't cause check → make it
							chessBoard.movePiece(fromX, fromY, toX, toY);
							
							// Removed the Rook-specific code that was causing issues
							
							// Important: Let's set a legal response code so the Chess class 
							// will also update its internal board
							if (chessBoard.isInCheck(currentPlayer != 1)) {
								codeResponse = 41;  // Legal move that causes check
							} else {
								codeResponse = 42;  // Move successful without check
							}
							currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch turn
						}
					}
				}
			}
		}
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}