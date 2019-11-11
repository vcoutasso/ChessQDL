#ifndef CHESSQDL_MOVEGEN_H
#define CHESSQDL_MOVEGEN_H

#include "bitboard.h"

namespace chessqdl {

	class MoveGenerator {

	public:
		MoveGenerator() = default;

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


	};

}


#endif //CHESSQDL_MOVEGEN_H
