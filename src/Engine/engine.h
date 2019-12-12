#ifndef CHESSQDL_ENGINE_H
#define CHESSQDL_ENGINE_H

#include "bitboard.h"
#include "movegen.h"

#include <stack>

namespace chessqdl {

    class Engine {
    private:
        Bitboard bitboard;

		MoveGenerator generator;

		enumColor toMove;
		enumColor pieceColor;

		std::stack<std::string> moveHistory;
		std::stack<enumColor> captureHistory;

		int ply = 0;
		int difficulty = 4;

        void printBoard();

    public:
        Engine();

		Engine(enumColor color);

		Engine(std::string fen, enumColor color);

		void parser();

		void makeMove(std::string mv, bool verbose = true);

		void unmakeMove();

		enumColor getToMove();

		std::string getBestMove(U64 *board, int depth, enumColor color);

		int alphaBetaMax(U64 *board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited,
						 std::string &bestMove);

		int alphaBetaMin(U64 *board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited,
						 std::string &bestMove);

    };

}

#endif //CHESSQDL_ENGINE_H
