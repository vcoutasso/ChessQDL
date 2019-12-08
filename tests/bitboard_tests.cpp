#include "gtest/gtest.h"
#include "../src/Engine/bitboard.h"

TEST(Bitboard, InitStandardChessBoard_Test) {
	chessqdl::Bitboard bitboard;

	EXPECT_EQ(bitboard.getPawns(chessqdl::enumColor::nWhite), 0xff00);
	EXPECT_EQ(bitboard.getPawns(chessqdl::enumColor::nBlack), 0xff000000000000);

	EXPECT_EQ(bitboard.getKnights(chessqdl::enumColor::nWhite), 0x42);
	EXPECT_EQ(bitboard.getKnights(chessqdl::enumColor::nBlack), 0x4200000000000000);

	EXPECT_EQ(bitboard.getBishops(chessqdl::enumColor::nWhite), 0x24);
	EXPECT_EQ(bitboard.getBishops(chessqdl::enumColor::nBlack), 0x2400000000000000);

	EXPECT_EQ(bitboard.getRooks(chessqdl::enumColor::nWhite), 0x81);
	EXPECT_EQ(bitboard.getRooks(chessqdl::enumColor::nBlack), 0x8100000000000000);

	EXPECT_EQ(bitboard.getQueens(chessqdl::enumColor::nWhite), 0x08);
	EXPECT_EQ(bitboard.getQueens(chessqdl::enumColor::nBlack), 0x0800000000000000);

	EXPECT_EQ(bitboard.getKing(chessqdl::enumColor::nWhite), 0x10);
	EXPECT_EQ(bitboard.getKing(chessqdl::enumColor::nBlack), 0x1000000000000000);
}

TEST(Bitboard, FENConstructor_Test) {
	chessqdl::Bitboard fenConstructor("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	chessqdl::Bitboard defaultConstructor;

	EXPECT_EQ(fenConstructor.getPawns(chessqdl::enumColor::nColor),
			  defaultConstructor.getPawns(chessqdl::enumColor::nColor));
	EXPECT_EQ(fenConstructor.getKnights(chessqdl::enumColor::nColor),
			  defaultConstructor.getKnights(chessqdl::enumColor::nColor));
	EXPECT_EQ(fenConstructor.getBishops(chessqdl::enumColor::nColor),
			  defaultConstructor.getBishops(chessqdl::enumColor::nColor));
	EXPECT_EQ(fenConstructor.getRooks(chessqdl::enumColor::nColor),
			  defaultConstructor.getRooks(chessqdl::enumColor::nColor));
	EXPECT_EQ(fenConstructor.getQueens(chessqdl::enumColor::nColor),
			  defaultConstructor.getQueens(chessqdl::enumColor::nColor));
	EXPECT_EQ(fenConstructor.getKing(chessqdl::enumColor::nColor),
			  defaultConstructor.getKing(chessqdl::enumColor::nColor));

}

