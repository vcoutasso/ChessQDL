#ifndef CHESSQDL_CONST_H
#define CHESSQDL_CONST_H

#include <map>
#include <string>

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


	const std::map<int, std::string> mapPositions = {{0,  "a1"},
													 {1,  "b1"},
													 {2,  "c1"},
													 {3,  "d1"},
													 {4,  "e1"},
													 {5,  "f1"},
													 {6,  "g1"},
													 {7,  "h1"},
													 {8,  "a2"},
													 {9,  "b2"},
													 {10, "c2"},
													 {11, "d2"},
													 {12, "e2"},
													 {13, "f2"},
													 {14, "g2"},
													 {15, "h2"},
													 {16, "a3"},
													 {17, "b3"},
													 {18, "c3"},
													 {19, "d3"},
													 {20, "e3"},
													 {21, "f3"},
													 {22, "g3"},
													 {23, "h3"},
													 {24, "a4"},
													 {25, "b4"},
													 {26, "c4"},
													 {27, "d4"},
													 {28, "e4"},
													 {29, "f4"},
													 {30, "g4"},
													 {31, "h4"},
													 {32, "a5"},
													 {33, "b5"},
													 {34, "c5"},
													 {35, "d5"},
													 {36, "e5"},
													 {37, "f5"},
													 {38, "g5"},
													 {39, "h5"},
													 {40, "a6"},
													 {41, "b6"},
													 {42, "c6"},
													 {43, "d6"},
													 {44, "e6"},
													 {45, "f6"},
													 {46, "g6"},
													 {47, "h6"},
													 {48, "a7"},
													 {49, "b7"},
													 {50, "c7"},
													 {51, "d7"},
													 {52, "e7"},
													 {53, "f7"},
													 {54, "g7"},
													 {55, "h7"},
													 {56, "a8"},
													 {57, "b8"},
													 {58, "c8"},
													 {59, "d8"},
													 {60, "e8"},
													 {61, "f8"},
													 {62, "g8"},
													 {63, "h8"}};

}

#endif //CHESSQDL_CONST_H
