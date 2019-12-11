#include "engine.h"
#include "utils.h"

#include <iostream>

using namespace chessqdl;

Engine::Engine() {
    bitboard = Bitboard();
	generator = MoveGenerator();

	auto moves = generator.getPseudoLegalMoves(bitboard.getBitBoards(), nColor);

	for (auto m : moves)
		std::cout << m << std::endl;
}

Engine::Engine(std::string fen) {
    bitboard = Bitboard(fen);
}

void Engine::printBoard() {
    bitboard.printBoard();
}

void Engine::start() {
    std::string input;

    while(true) {
        std::cout << "> ";
        std::cin >> input;

        if (input == "print" || input == "print_board")
            printBoard();
        else if (input == "move" || input == "mv") {
            // Reads the movement to be made
            std::cin >> input;

        }
        else if (input == "exit" || input == "quit")
            break;
        else
            continue;

    }

}


