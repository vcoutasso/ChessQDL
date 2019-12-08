#include "gtest/gtest.h"
#include "../src/Engine/bitboard.h"

TEST(Bitboard, InitStandardChessBoard_Test) {
	chessqdl::Bitboard board;

	EXPECT_EQ(board.getPawns(chessqdl::enumColor::nWhite), 0xffL << 8);
	EXPECT_EQ(board.getPawns(chessqdl::enumColor::nBlack), 0xffL << 48);

	EXPECT_EQ(board.getKnights(chessqdl::enumColor::nWhite), 0x42);
	EXPECT_EQ(board.getKnights(chessqdl::enumColor::nBlack), 0x42L << 56);

	EXPECT_EQ(board.getBishops(chessqdl::enumColor::nWhite), 0x24);
	EXPECT_EQ(board.getBishops(chessqdl::enumColor::nBlack), 0x24L << 56);

	EXPECT_EQ(board.getRooks(chessqdl::enumColor::nWhite), 0x81);
	EXPECT_EQ(board.getRooks(chessqdl::enumColor::nBlack), 0x81L << 56);

	EXPECT_EQ(board.getQueens(chessqdl::enumColor::nWhite), 0x08);
	EXPECT_EQ(board.getQueens(chessqdl::enumColor::nBlack), 0x08L << 56);

	EXPECT_EQ(board.getKing(chessqdl::enumColor::nWhite), 0x10);
	EXPECT_EQ(board.getKing(chessqdl::enumColor::nBlack), 0x10L << 56);
}

TEST(Bitboard, EvansGambitConstructor_Test) {
	chessqdl::Bitboard board("r1bqk1nr/pppp1ppp/2n5/2b1p3/1PB1P3/5N2/P1PP1PPP/RNBQK2R b KQkq b3 1 4");

	EXPECT_EQ(board.getPawns(chessqdl::enumColor::nWhite), 0x1200edL << 8);
	EXPECT_EQ(board.getPawns(chessqdl::enumColor::nBlack), 0xef0010L << 32);

	EXPECT_EQ(board.getKnights(chessqdl::enumColor::nWhite), 0x200002);
	EXPECT_EQ(board.getKnights(chessqdl::enumColor::nBlack), 0x400004L << 40);

	EXPECT_EQ(board.getBishops(chessqdl::enumColor::nWhite), 0x4000004);
	EXPECT_EQ(board.getBishops(chessqdl::enumColor::nBlack), 0x4000004L << 32);

	EXPECT_EQ(board.getRooks(chessqdl::enumColor::nWhite), 0x81);
	EXPECT_EQ(board.getRooks(chessqdl::enumColor::nBlack), 0x81L << 56);

	EXPECT_EQ(board.getQueens(chessqdl::enumColor::nWhite), 0x08);
	EXPECT_EQ(board.getQueens(chessqdl::enumColor::nBlack), 0x08L << 56);

	EXPECT_EQ(board.getKing(chessqdl::enumColor::nWhite), 0x10);
	EXPECT_EQ(board.getKing(chessqdl::enumColor::nBlack), 0x10L << 56);
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

