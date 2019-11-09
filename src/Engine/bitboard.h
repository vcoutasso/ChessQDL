#ifndef CHESSQDL_BITBOARD_H
#define CHESSQDL_BITBOARD_H

#include <bitset>

typedef std::bitset<64> U64;

namespace chessqdl {

	class Bitboard {
	private:
		U64 bitBoards[8];

	public:
		/**
		 * @brief Default constructor. Initializes bitBoards according to a default initial chess board.
		 */
		Bitboard();

		enum pieceColor {
			nWhite,			// all white pieces
			nBlack			// all black pieces
		};

		enum pieceType {
			nPawn=2,		// all pawns
			nKnight,		// all knights
			nBishop,		// all bishops
			nRook,			// all rooks
			nQueen,			// all queens
			nKing			// all kings
		};

		/**
		 * @brief Returns a bitboard containing all pawns of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all pawns of a given color piece
		 */
		U64 getPawns(pieceColor color);

		/**
		 * @brief Returns a bitboard containing all knights of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all knights of a given color piece
		 */
		U64 getKnights(pieceColor color);


		/**
		 * @brief Returns a bitboard containing all bishops of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all bishops of a given color piece
		 */
		U64 getBishops(pieceColor color);

		/**
		 * @brief Returns a bitboard containing all rooks of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all rooks of a given color piece
		 */
		U64 getRooks(pieceColor color);


		/**
		 * @brief Returns a bitboard containing all queens of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all queens of a given color piece
		 */
		U64 getQueens(pieceColor color);


		/**
		 * @brief Returns a bitboard containing the king of a given color piece
		 * @param color - the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing the king of a given color piece
		 */
		U64 getKing(pieceColor color);

		/**
		 * @brief Prints current state of the board to stdout. Mainly for debugging purposes.
		 */
		void printBoard();
	};

}

#endif //CHESSQDL_BITBOARD_H
