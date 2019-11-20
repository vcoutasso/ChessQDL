#include "gtest/gtest.h"
#include "../src/Engine/bitboard.h"

TEST(Bitboard, InitStandardChessBoard_Test) {
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

TEST(Bitboard, FENConstructor_Test) {
	chessqdl::Bitboard fenConstructor("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	chessqdl::Bitboard defaultConstructor;

	EXPECT_EQ(fenConstructor.getPawns(chessqdl::pieceColor::nColor), defaultConstructor.getPawns(chessqdl::pieceColor::nColor));
	EXPECT_EQ(fenConstructor.getKnights(chessqdl::pieceColor::nColor), defaultConstructor.getKnights(chessqdl::pieceColor::nColor));
	EXPECT_EQ(fenConstructor.getBishops(chessqdl::pieceColor::nColor), defaultConstructor.getBishops(chessqdl::pieceColor::nColor));
	EXPECT_EQ(fenConstructor.getRooks(chessqdl::pieceColor::nColor), defaultConstructor.getRooks(chessqdl::pieceColor::nColor));
	EXPECT_EQ(fenConstructor.getQueens(chessqdl::pieceColor::nColor), defaultConstructor.getQueens(chessqdl::pieceColor::nColor));
	EXPECT_EQ(fenConstructor.getKing(chessqdl::pieceColor::nColor), defaultConstructor.getKing(chessqdl::pieceColor::nColor));

}

