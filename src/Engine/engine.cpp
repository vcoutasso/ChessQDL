#include "engine.h"
#include "utils.h"

#include <iostream>
#include <algorithm>

using namespace chessqdl;


Engine::Engine() {
    bitboard = Bitboard();
	generator = MoveGenerator();
	pieceColor = nBlack;
	toMove = nWhite;
}


Engine::Engine(enumColor color) {
	bitboard = Bitboard();
	generator = MoveGenerator();
	pieceColor = color;
	toMove = nWhite;
}


Engine::Engine(std::string fen, enumColor color) {
    bitboard = Bitboard(fen);
	pieceColor = color;
	// FIXME: toMove actually depends on the fen string.
	toMove = nWhite;
}


void Engine::printBoard() {
    bitboard.printBoard();
}


enumColor Engine::getToMove() {
	return toMove;
}


void Engine::parser() {
    std::string input;

    while(true) {
        std::cout << "> ";
        std::cin >> input;

        if (input == "print" || input == "print_board")
            printBoard();
        else if (input == "move" || input == "mv") {
            // Reads the movement to be made
            std::cin >> input;
			movePiece(input);

        }
        else if (input == "exit" || input == "quit")
            break;
        else
            continue;

    }

}


void Engine::movePiece(std::string mv) {
	auto pseudoLegal = generator.getPseudoLegalMoves(bitboard.getBitBoards(), toMove);
	bool found = std::find(pseudoLegal.begin(), pseudoLegal.end(), mv) != pseudoLegal.end();

	enumColor otherPlayer;

	if (getToMove() == nWhite)
		otherPlayer = nBlack;
	else
		otherPlayer = nWhite;

	if (!found)
		std::cout << "Invalid move!" << std::endl;
	else {
		std::string from = mv.substr(0, 2);
		std::string to = mv.substr(2);

		auto fromIt = std::find(mapPositions.begin(), mapPositions.end(), from);
		auto toIt = std::find(mapPositions.begin(), mapPositions.end(), to);

		int fromIdx = std::distance(mapPositions.begin(), fromIt);
		int toIdx = std::distance(mapPositions.begin(), toIt);

		enumPiece pieceType = nPawn;

		U64 *bb = bitboard.getBitBoards();

		for (int i = nPawn; i <= nKing; i++) {
			U64 aux = bb[i] & bb[toMove];
			if (aux.test(fromIdx)) {
				pieceType = enumPiece(i);
				break;
			}
		}

		bb[pieceType].reset(fromIdx);
		bb[toMove].reset(fromIdx);
		bb[pieceType].set(toIdx);
		bb[toMove].set(toIdx);

		// If a piece is being captured
		if (bb[otherPlayer].test(toIdx)) {
			bb[otherPlayer].reset(toIdx);
			for (int i = nPawn; i <= nKing; i++) {
				U64 aux = bb[i] & bb[otherPlayer];
				if (aux.test(toIdx)) {
					aux.reset(toIdx);
					break;
				}
			}
		}

		toMove = otherPlayer;
	}
}


