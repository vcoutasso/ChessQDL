#ifndef CHESSQDL_CONST_H
#define CHESSQDL_CONST_H

#include <vector>
#include <string>
#include <bitset>
#include <limits>

namespace chessqdl {

	/**
	 * @brief Analogous to uint64, but bitset is used to take advantage of its methods.
	 */
	typedef std::bitset<64> U64;

	/**
	 * @brief Constants representing the board with all bits set except for A or H file
	 */
	const U64 notAFile = 0xfefefefefefefefe;
	const U64 notHFile = 0x7f7f7f7f7f7f7f7f;

	/**
	 * @brief Bitboard array indexing by color
	 */
	enum enumColor {
		nWhite,			// all white pieces
		nBlack,			// all black pieces
		nColor			// all pieces
	};

	/**
	 * @brief Bitboard array indexing by piece
	 */
	enum enumPiece {
		nPawn=3,		// all pawns
		nKnight,		// all knights
		nBishop,		// all bishops
		nRook,			// all rooks
		nQueen,			// all queens
		nKing			// all kings
	};

	/**
	 * @brief Little-Endian Rank-File Mapping
	 */
	enum enumPositions {
		a1, b1, c1, d1, e1, f1, g1, h1,
		a2, b2, c2, d2, e2, f2, g2, h2,
		a3, b3, c3, d3, e3, f3, g3, h3,
		a4, b4, c4, d4, e4, f4, g4, h4,
		a5, b5, c5, d5, e5, f5, g5, h5,
		a6, b6, c6, d6, e6, f6, g6, h6,
		a7, b7, c7, d7, e7, f7, g7, h7,
		a8, b8, c8, d8, e8, f8, g8, h8
	};

	/**
	 * @brief Amount of bits to be shifted when moving a bit to the direction. Compass rose for reference:
	 *
	 *		noWe         nort         noEa
	 *				+7    +8    +9
	 *					\  |  /
	 *		west    -1 <-  0 -> +1    east
	 *					/  |  \
	 *				-9    -8    -7
	 *		soWe         sout         soEa
	 */
	enum enumDirections {
		noWe = 7,
		nort = 8,
		noEa = 9,
		west = -1,
		east = 1,
		soWe = -9,
		sout = -8,
		soEa = -7
	};


	/**
	 * @brief Maps the name of the position to the index of the equivalent bit set
	 */
	const std::vector<std::string> mapPositions = {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
												   "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
												   "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
												   "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
												   "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
												   "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
												   "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
												   "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"};

	const int intMin = std::numeric_limits<int>::min();
	const int intMax = std::numeric_limits<int>::max();

}

#endif //CHESSQDL_CONST_H
