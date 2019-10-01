#ifndef CHESSQDL_BOARD_H
#define CHESSQDL_BOARD_H

#include <iostream>
#include "tile.h"

typedef unsigned long long U64;

namespace xqdl {

	class Board {
	private:
		std::string FEN;
		U64 bitBoards[8];

		void fenToBitboard();

	public:
		Board();

		Board(std::string fen);

		enum class enumPiece {
			nWhite,        // any white piece
			nBlack,        // any black piece
			nPawn,        // any pawn
			nKnight,
			nBishop,
			nRook,
			nQueen,
			nKing
		};
	};

}


#endif //CHESSQDL_BOARD_H
