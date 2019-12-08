#ifndef CHESSQDL_ENGINE_H
#define CHESSQDL_ENGINE_H

#include "bitboard.h"

namespace chessqdl {

    class Engine {
    private:
        Bitboard bitboard;

        void printBoard();
    public:
        Engine();
        explicit Engine(std::string &fen);

        void start();

    };

}

#endif //CHESSQDL_ENGINE_H
