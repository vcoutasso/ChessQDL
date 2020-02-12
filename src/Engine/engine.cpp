#include "engine.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace chessqdl;


Engine::Engine() {
    bitboard = Bitboard();
	pieceColor = nBlack;
}


Engine::Engine(enumColor color) {
	bitboard = Bitboard();
	pieceColor = color;
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

void Engine::setDepth(int n) {
	if (n > 0) {
		std::cout << "New max search depth: " << n << std::endl;
		depthLevel = n;
	}
}


void Engine::parser() {
    std::string input;

    while(true) {
		if (pieceColor == toMove)
			makeMove(getBestMove(bitboard.getBitBoards(), depthLevel, pieceColor));

        std::cout << "> ";
        std::cin >> input;

        if (input == "print" || input == "print_board")
            printBoard();
        else if (input == "move" || input == "mv") {
            // Reads the movement to be made
            std::cin >> input;
			makeMove(input);
		} else if (input == "undo") {
			int num;
			std::cin >> num;
			for (int i = 0; i < num; i++)
				unmakeMove();
		} else if (input == "depth" || input == "set_depth") {
			int d;
			std::cin >> d;
			setDepth(d);
		} else if (input == "exit" || input == "quit")
			break;
		else
			continue;

		if (bitboard.getKing(nWhite) == 0) {
			std::cout << std::endl << "Game over! Black wins :)" << std::endl;
			break;
		} else if (bitboard.getKing(nBlack) == 0) {
			std::cout << std::endl << "Game over! White wins :)" << std::endl;
			break;
		}

    }

}


void Engine::makeMove(std::string mv, bool verbose) {
	auto pseudoLegal = MoveGenerator::getPseudoLegalMoves(bitboard.getBitBoards(), toMove);
	bool found = std::find(pseudoLegal.begin(), pseudoLegal.end(), mv) != pseudoLegal.end();

	enumColor otherPlayer;

	if (toMove == nWhite)
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

		switch (pieceType) {
			case nKnight:
				mv.insert(0, "N");
				break;
			case nBishop:
				mv.insert(0, "B");
				break;
			case nRook:
				mv.insert(0, "R");
				break;
			case nQueen:
				mv.insert(0, "Q");
				break;
			case nKing:
				mv.insert(0, "K");
				break;
			default:
				break;
		}

		// If a piece is being captured
		if (bb[otherPlayer].test(toIdx)) {
			for (int i = nPawn; i <= nKing; i++) {
				U64 aux = bb[i] & bb[otherPlayer];
				if (aux.test(toIdx)) {
					bb[i].reset(toIdx);
					captureHistory.push(enumColor(i));
					mv.insert(mv.find_first_of("12345678") + 1, "x");
					break;
				}
			}

			bb[otherPlayer].reset(toIdx);
		}

		bb[pieceType].reset(fromIdx);
		bb[toMove].reset(fromIdx);
		bb[pieceType].set(toIdx);
		bb[toMove].set(toIdx);

		bitboard.updateBitboard();

		if (ply % 2 == 0)
			mv = std::to_string(ply / 2 + 1) + ". " + mv;

		++ply;

		moveHistory.push(mv);

		toMove = otherPlayer;

		if (verbose)
			std::cout << mv << std::endl;
	}
}


void Engine::unmakeMove() {

	if (!moveHistory.empty()) {

		std::string lastMove = moveHistory.top();
		moveHistory.pop();

		if (lastMove.find(" ") != std::string::npos) {
			lastMove = lastMove.substr(lastMove.find(" ") + 1);
		}

		enumPiece pieceType = nPawn;
		bool captured = false;

		if (lastMove.find_first_of("NBRQK") != std::string::npos) {
			if (lastMove.at(0) == 'N')
				pieceType = nKnight;
			else if (lastMove.at(0) == 'B')
				pieceType = nBishop;
			else if (lastMove.at(0) == 'R')
				pieceType = nRook;
			else if (lastMove.at(0) == 'Q')
				pieceType = nQueen;
			else if (lastMove.at(0) == 'K')
				pieceType = nKing;

			lastMove.erase(0, 1);
		}

		if (lastMove.find("x") != std::string::npos) {
			captured = true;
			lastMove.erase(lastMove.find("x"), 1);
		}

		std::string from = lastMove.substr(0, 2);
		std::string to = lastMove.substr(2);

		auto fromIt = std::find(mapPositions.begin(), mapPositions.end(), from);
		auto toIt = std::find(mapPositions.begin(), mapPositions.end(), to);

		int fromIdx = std::distance(mapPositions.begin(), fromIt);
		int toIdx = std::distance(mapPositions.begin(), toIt);

		U64 *bb = bitboard.getBitBoards();

		enumColor hasMoved = toMove == nWhite ? nBlack : nWhite;

		bb[pieceType].reset(toIdx);
		bb[hasMoved].reset(toIdx);
		bb[pieceType].set(fromIdx);
		bb[hasMoved].set(fromIdx);

		if (captured) {
			enumColor capturedPiece = captureHistory.top();
			captureHistory.pop();

			bb[toMove].set(toIdx);
			bb[capturedPiece].set(toIdx);
		}

		bitboard.updateBitboard();

		toMove = hasMoved;

		--ply;
	}
}

std::string Engine::getBestMove(U64 *board, int depth, enumColor color) {
	std::string bestMove;
	int nodesVisited = 0;

	auto begin = std::chrono::steady_clock::now();

	alphaBetaMax(board, intMin, intMax, depth, depth, color, nodesVisited, bestMove);

	auto end = std::chrono::steady_clock::now();

	std::cout << "Best move found: " << bestMove << std::endl;
	std::cout << "Nodes visited: " << nodesVisited << std::endl;
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;


	return bestMove;
}

int Engine::alphaBetaMax(U64 *board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited, std::string &bestMove) {
	if (depthLeft == 0)
		return evaluateBoard(board, color);

	auto allMoves = MoveGenerator::getPseudoLegalMoves(board, color);

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(allMoves), std::end(allMoves), rng);

	enumColor enemyColor = color == nWhite ? nBlack : nWhite;

	for (auto &currentMove : allMoves) {

		nodesVisited++;

		makeMove(currentMove, false);
		int score = alphaBetaMin(board, alpha, beta, depth, depthLeft - 1, enemyColor, nodesVisited, bestMove);
		unmakeMove();

		if (score >= beta)
			return beta;
		if (score > alpha) {
			alpha = score;
			if (depth == depthLeft)
				bestMove = currentMove;
			//std::cout << "New move found for depth " << depth << " " << currentMove << " score: " << score << std::endl;
		}
	}
	return alpha;
}

int Engine::alphaBetaMin(U64 *board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited, std::string &bestMove) {

	if (depthLeft == 0)
		return -evaluateBoard(board, color);

	auto allMoves = MoveGenerator::getPseudoLegalMoves(board, color);

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(allMoves), std::end(allMoves), rng);

	enumColor enemyColor = color == nWhite ? nBlack : nWhite;

	for (auto &currentMove : allMoves) {

		nodesVisited++;

		makeMove(currentMove, false);
		int score = alphaBetaMax(board, alpha, beta, depth, depthLeft - 1, enemyColor, nodesVisited, bestMove);
		unmakeMove();

		if (score <= alpha)
			return alpha;
		if (score < beta) {
			beta = score;
			//std::cout << "New move found for depth " << depth << " " << currentMove << " score: " << score << std::endl;
		}
	}
	return beta;
}
