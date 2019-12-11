#ifndef CHESSQDL_BITBOARD_H
#define CHESSQDL_BITBOARD_H

#include <bitset>

#include "const.h"

namespace chessqdl {

	class Bitboard {

	private:
		/**
		 * @brief Array containing all bitboards. Indexing follows numColor and enumPiece
		 */
		U64 bitBoards[9];

	public:

		/**
		 * @brief Default constructor. Initializes bitBoards according to a default initial chess board.
		 */
		Bitboard();

		/**
		 * @brief FEN constructor. Initializes bitBoards according to the given FEN string.
		 */
		explicit Bitboard(std::string fen);

		/**
		 * @brief Returns a bitboard containing all pawns of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all pawns of a given color piece
		 */
		U64 getPawns(enumColor color);


		/**
		 * @brief Returns a bitboard containing all knights of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all knights of a given color piece
		 */
		U64 getKnights(enumColor color);


		/**
		 * @brief Returns a bitboard containing all bishops of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all bishops of a given color piece
		 */
		U64 getBishops(enumColor color);


		/**
		 * @brief Returns a bitboard containing all rooks of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all rooks of a given color piece
		 */
		U64 getRooks(enumColor color);


		/**
		 * @brief Returns a bitboard containing all queens of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all queens of a given color piece
		 */
		U64 getQueens(enumColor color);


		/**
		 * @brief Returns a bitboard containing the king of a given color piece
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing the king of a given color piece
		 */
		U64 getKing(enumColor color);


		/**
		 * @brief Returns a bitboard containing all pieces of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all pieces of a given color piece
		 */
		U64 getPieces(enumColor color);


		/**
		 * @brief Returns a bitboard containing all board pieces
		 * @return a bitboard containing all board pieces
		 */
		U64 getAllPieces();


		/**
		 * @brief Returns the bitBoard attribute of the class
		 * @return an array containing all bitboards
		 */
		U64 *getBitBoards();


		/**
		 * @brief Prints current state of the board to stdout. Mainly for debugging purposes.
		 */
		void printBoard();


		void updateBitBoards();

	};

}

#endif //CHESSQDL_BITBOARD_H
