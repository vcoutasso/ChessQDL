#include "gtest/gtest.h"
#include "../src/Engine/movegen.h"
#include "../src/Engine/bitboard.h"

//FIXME: These tests do not take into account the possibility of a pawn moving two squares on first move, castles or en passant captures

TEST(MoveGenerator, PseudoLegalInitialMoves_Test) {

	chessqdl::Bitboard bitboard;
	chessqdl::MoveGenerator generator;

	EXPECT_EQ(generator.getKnightMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0xa50000a50000);
	EXPECT_EQ(generator.getPawnMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor),
			  0xffffL << 16 | 0xffffL << 32);
	EXPECT_EQ(generator.getKingMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0x00);
	EXPECT_EQ(generator.getBishopMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor,
									   chessqdl::enumPiece::nBishop), 0x00);
	EXPECT_EQ(generator.getRookMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor, chessqdl::enumPiece::nRook),
			  0x00);
	EXPECT_EQ(generator.getQueenMoves(bitboard.getBitBoards(), chessqdl::enumColor::nColor), 0x00);

}

TEST (MoveGenerator, PseudoLegalEvansGambitMoves_test) {

	chessqdl::Bitboard board("r1bqk1nr/pppp1ppp/2n5/2b1p3/1PB1P3/5N2/P1PP1PPP/RNBQK2R b KQkq b3 1 4");
	chessqdl::MoveGenerator generator;

	EXPECT_EQ(generator.getPawnMoves(board.getBitBoards(), chessqdl::enumColor::nWhite), 0x6c9cdL << 16);
	EXPECT_EQ(generator.getPawnMoves(board.getBitBoards(), chessqdl::enumColor::nBlack), 0xebebL << 32);

	EXPECT_EQ(generator.getKnightMoves(board.getBitBoards(), chessqdl::enumColor::nWhite), 0x5088050040L);
	EXPECT_EQ(generator.getKnightMoves(board.getBitBoards(), chessqdl::enumColor::nBlack), 0x210a0010aL << 24);

	EXPECT_EQ(generator.getBishopMoves(board.getBitBoards(), chessqdl::enumColor::nWhite, chessqdl::enumPiece::nBishop),
			  0x20110a000b1220L);
	EXPECT_EQ(generator.getBishopMoves(board.getBitBoards(), chessqdl::enumColor::nBlack, chessqdl::enumPiece::nBishop),
			  0x20100a000a1020L << 8);

	EXPECT_EQ(generator.getRookMoves(board.getBitBoards(), chessqdl::enumColor::nWhite, chessqdl::enumPiece::nRook),
			  0x60);
	EXPECT_EQ(generator.getRookMoves(board.getBitBoards(), chessqdl::enumColor::nBlack, chessqdl::enumPiece::nRook),
			  0x02L << 56);

	EXPECT_EQ(generator.getQueenMoves(board.getBitBoards(), chessqdl::enumColor::nWhite), 0x10L << 8);
	EXPECT_EQ(generator.getQueenMoves(board.getBitBoards(), chessqdl::enumColor::nBlack), 0x10204080L << 24);

	EXPECT_EQ(generator.getKingMoves(board.getBitBoards(), chessqdl::enumColor::nWhite), 0x1020L);
	EXPECT_EQ(generator.getKingMoves(board.getBitBoards(), chessqdl::enumColor::nBlack), 0x2010L << 48);

}