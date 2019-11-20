#include "gtest/gtest.h"
#include "../src/Engine/movegen.h"
#include "../src/Engine/bitboard.h"

//TODO: Finish implementation of this test. Find and fix bug.
// I think I may be handling references incorrectly. Investigate on that.

TEST(MoveGenerator, PseudoLegalPawnsMoves_Test) {

	chessqdl::Bitboard bitboard;
	chessqdl::MoveGenerator generator;

	EXPECT_EQ(generator.getPawnMoves(*bitboard.getBitBoards(), chessqdl::pieceColor::nColor), 0xff0000ff0000);



}