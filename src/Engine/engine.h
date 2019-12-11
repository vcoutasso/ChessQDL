#ifndef CHESSQDL_ENGINE_H
#define CHESSQDL_ENGINE_H

#include "bitboard.h"
#include "movegen.h"

namespace chessqdl {

    class Engine {
    private:
        Bitboard bitboard;
		MoveGenerator generator;

		enumColor toMove;

		enumColor pieceColor;

        void printBoard();

    public:
        Engine();

		Engine(enumColor color);

		Engine(std::string fen, enumColor color);

		void parser();

		void movePiece(std::string mv);

		enumColor getToMove();

    };

}

#endif //CHESSQDL_ENGINE_H
