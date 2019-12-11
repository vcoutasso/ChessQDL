#ifndef CHESSQDL_ENGINE_H
#define CHESSQDL_ENGINE_H

#include "bitboard.h"
#include "movegen.h"

namespace chessqdl {

    class Engine {
    private:
        Bitboard bitboard;
		MoveGenerator generator;

        void printBoard();
    public:
        Engine();

		explicit Engine(std::string fen);

        void start();

    };

}

#endif //CHESSQDL_ENGINE_H
