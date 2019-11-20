#ifndef CHESSQDL_MOVEGEN_H
#define CHESSQDL_MOVEGEN_H

#include "bitboard.h"

namespace chessqdl {

	class MoveGenerator {

	private:

		/* Constants representing the board with all bits set except for one file */
		const U64 notAFile = 0xfefefefefefefefe;
		const U64 notHFile = 0x7f7f7f7f7f7f7f7f;


		/**
		 * @brief Shifts bitboard one up and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one up
		 */
		U64 shiftNorth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one up, one right and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one up one right
		 */
		U64 shiftNorthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one right
		 */
		U64 shiftEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right one down and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one right one down
		 */
		U64 shiftSouthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one down
		 */
		U64 shiftSouth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down one left and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one down one left
		 */
		U64 shiftSouthWest(U64 bitboard);


		/**
		 * @brief Shifts bitboard one left and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one left
		 */
		U64 shiftWest(U64 bitboard);


		/**
		 * @brief Shifts bitboard one left one up and returns it
		 * @param bitboard - bitboard to be shifted
		 * @return Bitboard shifted one left one up
		 */
		U64 shiftNorthWest(U64 bitboard);


	public:

		MoveGenerator() = default;


		/**
		 * @brief Get pseudo-legal moves for a given color set of pawns
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for pawns.
		 */
		U64 getPawnMoves(const U64 &bitboard, pieceColor color);


		/**
		 * @brief Get pseudo-legal moves for a given king
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for king.
		 */
		U64 getKingMoves(const U64 &bitboard, pieceColor color);


		/**
		 * @brief Get pseudo-legal moves for a given color set of knights
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for knights of a given color.
		 */
		U64 getKnightMoves(const U64 &bitboard, pieceColor color);


	};

}

#endif //CHESSQDL_MOVEGEN_H
