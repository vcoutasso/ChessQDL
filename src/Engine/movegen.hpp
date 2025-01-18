#ifndef CHESSQDL_MOVEGEN_HPP
#define CHESSQDL_MOVEGEN_HPP

#include "bitboard.hpp"

#include <cstdint>
#include <vector>

namespace chessqdl {

	class MoveGenerator {

	private:

		/**
		 * @brief Shifts bitboard one up and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one up
		 */
		static U64 shiftNorth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one up, one right and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one up one right
		 */
		static U64 shiftNorthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one right
		 */
		static U64 shiftEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one right one down and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one right one down
		 */
		static U64 shiftSouthEast(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one down
		 */
		static U64 shiftSouth(U64 bitboard);


		/**
		 * @brief Shifts bitboard one down one left and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one down one left
		 */
		static U64 shiftSouthWest(U64 bitboard);


		/**
		 * @brief Shifts bitboard one left and returns it
		 * @param bitboard  bitboard to be shifted
		 * @return Bitboard shifted one left
		 */
		static U64 shiftWest(U64 bitboard);


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
		static U64 soutOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the north direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 nortOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the east direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 eastOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the northeast direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 noEaOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the southeast direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 soEaOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the west direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 westOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the southwest direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 soWeOccl(U64 generator, U64 propagator);


		/**
		 * @brief Generates ray-wise moves in the northwest direction, excluding blockers but \b including sliders
		 * @param generator   sliding pieces
		 * @param propagator  empty board
		 * @return Bitboard with all possible moves AND the actual position of slider pieces (original \p generator)
		 */
		static U64 noWeOccl(U64 generator, U64 propagator);

	public:

		MoveGenerator() = default;


		/**
		 * @brief Get pseudo-legal moves for a given color set of pawns
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @return Bitboard with pseudo-legal moves for pawns.
		 */
		static U64 getPawnMoves(const BitboardArray &bitboard, enumColor color);


		/**
		 * @brief Get pseudo-legal moves for a given king
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @return Bitboard with pseudo-legal moves for king.
		 */
		static U64 getKingMoves(const BitboardArray &bitboard, enumColor color);


		/**
		 * @brief Get pseudo-legal moves for a given color set of knights
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @return Bitboard with pseudo-legal moves for knights of a given color.
		 */
		static U64 getKnightMoves(const BitboardArray &bitboard, enumColor color);


		/**
		 * @brief Get pseudo-legal bishop moves for a given color set
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @param piece  piece type (bishop or queen)
		 * @return Bitboard with pseudo-legal moves for bishops or queens of a given color.
		 */
		static U64 getBishopMoves(const BitboardArray &bitboard, enumColor color, enumPiece piece = nBishop);


		/**
		 * @brief Get pseudo-legal rook moves for a given color set
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @param piece  piece type (rook or queen)
		 * @return Bitboard with pseudo-legal moves for rooks or queens of a given color.
		 */
		static U64 getRookMoves(const BitboardArray &bitboard, enumColor color, enumPiece piece = nRook);


		/**
		 * @brief Get pseudo-legal moves for a given color set of queens
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @return Bitboard with pseudo-legal moves for queens of a given color.
		 */
		static U64 getQueenMoves(const BitboardArray &bitboard, enumColor color);


		/**
		 * @brief Checks for pawns that are about to promote and generates moves for all possible promotions
		 * @param pawnMoves  all possible pawn moves
		 * @param fromPos  position of pawn
		 * @return Vector with all possible promotions. (e.g e7e8n e7e8b e7e8r e7e8q)
		 */
		static std::vector<std::string> getPawnPromotions(U64 &pawnMoves, uint64_t fromPos);

		/**
		 * @brief Get all possible pseudo-legal moves for a given bitboard
		 * @param bitboard  reference to bitboards representing the current board status
		 * @param color  color of desired piece
		 * @return  a list of all possible moves (e.g "e2e4", "b1c3", etc)
		 */
		static std::vector<std::string> getPseudoLegalMoves(const BitboardArray &bitboard, enumColor color);

	};

}

#endif //CHESSQDL_MOVEGEN_HPP
