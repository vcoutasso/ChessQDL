#include <gtest/gtest.h>
#include "../src/Engine/bitboard.h"

TEST(Bitboard, InitStandardChessBoard) {
	chessqdl::Bitboard bitboard;

	EXPECT_EQ(bitboard.getPawns(chessqdl::pieceColor::nWhite), 0xff00);
	EXPECT_EQ(bitboard.getPawns(chessqdl::pieceColor::nBlack), 0xff000000000000);

	EXPECT_EQ(bitboard.getKnights(chessqdl::pieceColor::nWhite), 0x42);
	EXPECT_EQ(bitboard.getKnights(chessqdl::pieceColor::nBlack), 0x4200000000000000);

	EXPECT_EQ(bitboard.getBishops(chessqdl::pieceColor::nWhite), 0x24);
	EXPECT_EQ(bitboard.getBishops(chessqdl::pieceColor::nBlack), 0x2400000000000000);

	EXPECT_EQ(bitboard.getRooks(chessqdl::pieceColor::nWhite), 0x81);
	EXPECT_EQ(bitboard.getRooks(chessqdl::pieceColor::nBlack), 0x8100000000000000);

	EXPECT_EQ(bitboard.getQueens(chessqdl::pieceColor::nWhite), 0x08);
	EXPECT_EQ(bitboard.getQueens(chessqdl::pieceColor::nBlack), 0x0800000000000000);

	EXPECT_EQ(bitboard.getKing(chessqdl::pieceColor::nWhite), 0x10);
	EXPECT_EQ(bitboard.getKing(chessqdl::pieceColor::nBlack), 0x1000000000000000);
}


