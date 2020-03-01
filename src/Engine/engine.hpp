#ifndef CHESSQDL_ENGINE_HPP
#define CHESSQDL_ENGINE_HPP

#include "bitboard.hpp"
#include "movegen.hpp"

#include <stack>

namespace chessqdl {

	class Engine {

	private:

		/**
		 * @brief Bitboard representation of the current board state
		 */
		Bitboard bitboard;

		/**
		 * @brief Color of the pieces to move
		 */
		enumColor toMove = nWhite;

		/**
		 * @brief Color of the engine's pieces
		 */
		enumColor pieceColor;

		/**
		 * @brief Stack with moves history. Used to undo moves
		 */
		std::stack<std::string> moveHistory;

		/**
		 * @brief Stack with capture history. Used to undo captures
		 */
		std::stack<enumColor> captureHistory;

		/**
		 * @brief Ply counter. The counter is incremented after every valid move made and decremented after each undo
		 */
		int ply = 0;

		/**
		 * @brief This variable determines how deep into the moves tree the algorithm should go when searching for the optimal move
		 */
		int depthLevel;

		/**
		 * @brief When set to true the engine will display more information about the process of finding a move
		 */
		bool beVerbose;

		/**
		 * @brief Prints the current state of the board to stdout. A terminal with unicode support is recommended since the pieces are represented by unicode symbols
		 */
		void printBoard();

	public:


		/**
		 * @brief Overloaded constructor. Allows the selection of the engine's pieces.
		 * @param color  the color of the engine's pieces
		 */
		Engine(enumColor color, int depth, bool v);


		/**
		 * @brief Overloaded constructor. Starts a game of chess equivalent to the \p fen string parameter
		 * @param fen  valid fen string that represents a chess game
		 * @param color  color of the pieces the engine will assume
		 */
		Engine(std::string fen, enumColor color, int depth, bool v);


		/**
		 * @brief Player input parser. Acts as an interface to the engine
		 */
		void parser();


		/**
		 * @brief Effectively makes a move (only if \p mv represents a valid move), updates the bitboards and prints to stdout the move made (if \p verbose)
		 * @param mv  string with move to be made
		 * @param verbose  sets whether or not the movement made should be printed to stdout. Defaults to true
		 */
		void makeMove(std::string mv, bool verbose = true);


		/**
		 * @brief Takes back the most recent move
		 */
		void takeMove();


		/**
		 * @brief Get method that returns the color of the player to make a move
		 * @return the value of Engine::toMove
		 */
		enumColor getToMove();


		/**
		 * @brief Maximum depth allowed for tree traversal when searching for moves
		 * @param n  maximum depth
		 */
		void setDepth(int n);


		/**
		 * @brief Traverses the tree of movements up to \p depth and returns the best move the algorithm has found
		 * @param board  current board state
		 * @param depth  maximum traversal depth
		 * @param color  color of the pieces for which to find the best move
		 * @return
		 */
		std::string getBestMove(BitbArray board, int depth, enumColor color);


		/**
		 * @brief Max implementation of the Minimax algorithm with alpha-beta pruning
		 * @param board  current board state
		 * @param alpha  score to be maximized
		 * @param beta  score to be minimized
		 * @param depth  maximum traversal depth
		 * @param depthLeft  how far the algorithm is from reaching the max depth.
		 * @param color  color of the moving pieces
		 * @param nodesVisited  quantity of nodes visited
		 * @param bestMove  best move the algorithm has found
		 * @return returns the value of \p alpha
		 */
		int alphaBetaMax(BitbArray &board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited, std::string &bestMove);


		/**
		 * @brief Min implementation of the Minimax algorithm with alpha-beta pruning
		 * @param board  current board state
		 * @param alpha  score to be maximized
		 * @param beta  score to be minimized
		 * @param depth  maximum traversal depth
		 * @param depthLeft  how far the algorithm is from reaching the max depth.
		 * @param color  color of the moving pieces
		 * @param nodesVisited  quantity of nodes visited
		 * @param bestMove  best move the algorithm has found
		 * @return returns the value of \p beta
		 */
		int alphaBetaMin(BitbArray &board, int alpha, int beta, int depth, int depthLeft, enumColor color, int &nodesVisited, std::string &bestMove);

    };

}

#endif //CHESSQDL_ENGINE_HPP
