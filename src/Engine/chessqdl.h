#ifndef CHESSQDL_CHESSQDL_H
#define CHESSQDL_CHESSQDL_H

#include <map>
#include <string>

namespace chessqdl {

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

	extern std::map<int, std::string> mapPositions;
}

#endif //CHESSQDL_CHESSQDL_H
