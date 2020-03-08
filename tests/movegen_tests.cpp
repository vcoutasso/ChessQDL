#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Engine/movegen.hpp"
#include "Engine/bitboard.hpp"
#include "Engine/utils.hpp"

//FIXME: These tests do not take into account the possibility of castles or en passant captures

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

	EXPECT_EQ(generator.getPseudoLegalMoves(bitboard.getBitBoards(), chessqdl::enumColor::nWhite).size(), 20);
	EXPECT_EQ(generator.getPseudoLegalMoves(bitboard.getBitBoards(), chessqdl::enumColor::nBlack).size(), 20);

}

TEST(MoveGenerator, PseudoLegalEvansGambitMoves_Test) {

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

TEST(MoveGenerator, PawnPromotionAWhite_Test) {
	chessqdl::Bitboard board("1r2k3/P7/8/8/8/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("a7a8n", "a7a8b", "a7a8r", "a7a8q", "a7b8n", "a7b8b", "a7b8r", "a7b8q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionBWhite_Test) {
	chessqdl::Bitboard board("r1r1k3/1P6/8/8/8/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("b7a8n", "b7a8b", "b7a8r", "b7a8q", "b7b8n", "b7b8b", "b7b8r", "b7b8q", "b7c8n", "b7c8b", "b7c8r", "b7c8q"));
	EXPECT_EQ(moves, 0x0);
}


TEST(MoveGenerator, PawnPromotionCWhite_Test) {
	chessqdl::Bitboard board("1r1rk3/2P5/8/8/8/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("c7b8n", "c7b8b", "c7b8r", "c7b8q", "c7c8n", "c7c8b", "c7c8r", "c7c8q", "c7d8n", "c7d8b", "c7d8r", "c7d8q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionDWhite_Test) {
	chessqdl::Bitboard board("k1r1r3/3P4/8/8/8/8/8/3K4 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("d7c8n", "d7c8b", "d7c8r", "d7c8q", "d7d8n", "d7d8b", "d7d8r", "d7d8q", "d7e8n", "d7e8b", "d7e8r", "d7e8q"));
	EXPECT_EQ(moves, 0x0);
}


TEST(MoveGenerator, PawnPromotionEWhite_Test) {
	chessqdl::Bitboard board("k2r1r2/4P3/8/8/8/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("e7d8n", "e7d8b", "e7d8r", "e7d8q", "e7e8n", "e7e8b", "e7e8r", "e7e8q", "e7f8n", "e7f8b", "e7f8r", "e7f8q"));
	EXPECT_EQ(moves, 0x0);
}


TEST(MoveGenerator, PawnPromotionFWhite_Test) {
	chessqdl::Bitboard board("k3r1r1/5P2/8/8/8/8/8/5K2 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("f7e8n", "f7e8b", "f7e8r", "f7e8q", "f7f8n", "f7f8b", "f7f8r", "f7f8q", "f7g8n", "f7g8b", "f7g8r", "f7g8q"));
	EXPECT_EQ(moves, 0x0);
}


TEST(MoveGenerator, PawnPromotionGWhite_Test) {
	chessqdl::Bitboard board("k4r1r/6P1/8/8/8/8/8/6K1 w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("g7f8n", "g7f8b", "g7f8r", "g7f8q", "g7g8n", "g7g8b", "g7g8r", "g7g8q", "g7h8n", "g7h8b", "g7h8r", "g7h8q"));
	EXPECT_EQ(moves, 0x0);
}


TEST(MoveGenerator, PawnPromotionHWhite_Test) {
	chessqdl::Bitboard board("k5r1/7P/8/8/8/8/8/7K w - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nWhite).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("h7g8n", "h7g8b", "h7g8r", "h7g8q", "h7h8n", "h7h8b", "h7h8r", "h7h8q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionABlack_Test) {
	chessqdl::Bitboard board("k7/8/8/8/8/8/p7/1R1K4 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("a2a1n", "a2a1b", "a2a1r", "a2a1q", "a2b1n", "a2b1b", "a2b1r", "a2b1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionBBlack_Test) {
	chessqdl::Bitboard board("1k6/8/8/8/8/8/1p6/R1RK4 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("b2a1n", "b2a1b", "b2a1r", "b2a1q", "b2b1n", "b2b1b", "b2b1r", "b2b1q", "b2c1n", "b2c1b", "b2c1r", "b2c1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionCBlack_Test) {
	chessqdl::Bitboard board("2k5/8/8/8/8/8/2p5/KR1R4 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("c2b1n", "c2b1b", "c2b1r", "c2b1q", "c2c1n", "c2c1b", "c2c1r", "c2c1q", "c2d1n", "c2d1b", "c2d1r", "c2d1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionDBlack_Test) {
	chessqdl::Bitboard board("3k4/8/8/8/8/8/3p4/K1R1R3 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("d2c1n", "d2c1b", "d2c1r", "d2c1q", "d2d1n", "d2d1b", "d2d1r", "d2d1q", "d2e1n", "d2e1b", "d2e1r", "d2e1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionEBlack_Test) {
	chessqdl::Bitboard board("4k3/8/8/8/8/8/4p3/K2R1R2 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("e2d1n", "e2d1b", "e2d1r", "e2d1q", "e2e1n", "e2e1b", "e2e1r", "e2e1q", "e2f1n", "e2f1b", "e2f1r", "e2f1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionFBlack_Test) {
	chessqdl::Bitboard board("5k2/8/8/8/8/8/5p2/K3R1R1 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("f2e1n", "f2e1b", "f2e1r", "f2e1q", "f2f1n", "f2f1b", "f2f1r", "f2f1q", "f2g1n", "f2g1b", "f2g1r", "f2g1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionGBlack_Test) {
	chessqdl::Bitboard board("6k1/8/8/8/8/8/6p1/K4R1R b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("g2f1n", "g2f1b", "g2f1r", "g2f1q", "g2g1n", "g2g1b", "g2g1r", "g2g1q", "g2h1n", "g2h1b", "g2h1r", "g2h1q"));
	EXPECT_EQ(moves, 0x0);
}

TEST(MoveGenerator, PawnPromotionHBlack_Test) {
	chessqdl::Bitboard board("7k/8/8/8/8/8/7p/K5R1 b - - 0 1");
	chessqdl::MoveGenerator generator;

	chessqdl::U64 moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nBlack);
	std::vector<std::string> promotions = generator.getPawnPromotions(moves, 1L << chessqdl::leastSignificantSetBit(board.getPawns(chessqdl::nBlack).to_ullong()));

	EXPECT_THAT(promotions, testing::ElementsAre("h2g1n", "h2g1b", "h2g1r", "h2g1q", "h2h1n", "h2h1b", "h2h1r", "h2h1q"));
	EXPECT_EQ(moves, 0x0);
}
