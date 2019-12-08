#include "gtest/gtest.h"
#include "../src/Engine/movegen.h"
#include "../src/Engine/bitboard.h"

//TODO: Finish implementation of this test.

TEST(MoveGenerator, PseudoLegalPawnsMoves_Test) {

	chessqdl::Bitboard bitboard;
	chessqdl::MoveGenerator generator;

	EXPECT_EQ(generator.getKnightMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0xa50000a50000);
	EXPECT_EQ(generator.getPawnMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0xff0000ff0000);
	EXPECT_EQ(generator.getKingMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0x00);
	EXPECT_EQ(generator.getBishopMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor,
									   chessqdl::enumPiece::nBishop), 0x00);
	EXPECT_EQ(generator.getRookMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor, chessqdl::enumPiece::nRook),
			  0x00);
	EXPECT_EQ(generator.getQueenMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0x00);

}