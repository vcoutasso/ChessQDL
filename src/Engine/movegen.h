#ifndef CHESSQDL_MOVEGEN_H
#define CHESSQDL_MOVEGEN_H

#include "bitboard.h"

namespace chessqdl {

	class MoveGenerator {

	private:

		/**
		 * @brief Shifts bitboard one up and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one up
		 */
		U64 shiftNorth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one up, one right and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one up one right
		 */
		U64 shiftNorthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one right
		 */
		U64 shiftEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right one down and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one right one down
		 */
		U64 shiftSouthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one down
		 */
		U64 shiftSouth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down one left and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one down one left
		 */
		U64 shiftSouthWest(U64 bitboard);


		/**
		 * @brief Shifts bitboard one left and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one left
		 */
		U64 shiftWest(U64 bitboard);


		/**
		 * @brief Shifts bitboard one left one up and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one left one up
		 */
		static U64 shiftNorthWest(U64 bitboard);


		/**
		 * @brief Generates ray-wise moves in the south direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 soutOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the north direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 nortOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the east direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 eastOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the northeast direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 noEaOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the southeast direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 soEaOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the west direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 westOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the southwest direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 soWeOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the northwest direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		U64 noWeOccl(U64 generator, U64 propagator);

	public:

		MoveGenerator() = default;


		/**
		 * @brief Get pseudo-legal moves for a given color set of pawns
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for pawns.
		 */
		U64 getPawnMoves(const U64 *bitboard, enumColor color);


		/**
		 * @brief Get pseudo-legal moves for a given king
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for king.
		 */
		U64 getKingMoves(const U64 *bitboard, enumColor color);


		/**
		 * @brief Get pseudo-legal moves for a given color set of knights
		 * @param bitboard - reference to bitboards representing the current board status
		 * @param color - color of desired piece
		 * @return Bitboard with pseudo-legal moves for knights of a given color.
		 */
		U64 getKnightMoves(const U64 *bitboard, enumColor color);

		U64 getBishopMoves(const U64 *bitboard, enumColor color, enumPiece piece);

		U64 getRookMoves(const U64 *bitboard, enumColor color, enumPiece piece);

		U64 getQueenMoves(const U64 *bitboard, enumColor color);


	};

}

#endif //CHESSQDL_MOVEGEN_H
