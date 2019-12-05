#include "gtest/gtest.h"
#include "../src/Engine/movegen.h"
#include "../src/Engine/bitboard.h"

//TODO: Finish implementation of this test.

TEST(MoveGenerator, PseudoLegalPawnsMoves_Test) {

	chessqdl::Bitboard bitboard;
	chessqdl::MoveGenerator generator;

	EXPECT_EQ(generator.getKnightMoves(bitboard.getBitBoards(), chessqdl::pieceColor::nColor), 0xa50000a50000);
	EXPECT_EQ(generator.getPawnMoves(bitboard.getBitBoards(), chessqdl::pieceColor::nColor), 0xff0000ff0000);
    EXPECT_EQ(generator.getKingMoves(bitboard.getBitBoards(), chessqdl::pieceColor::nColor), 0x0);


}