#include "gtest/gtest.h"
#include "../src/Engine/movegen.h"

TEST(MoveGenerator, MoveGenerator_CheckShiftOperations_Test) {
	chessqdl::MoveGenerator generator;
	U64 bitboard = 0x400;

	EXPECT_EQ(generator.shiftNorth(bitboard), 0x40000);
	EXPECT_EQ(generator.shiftNorthEast(bitboard), 0x80000);
	EXPECT_EQ(generator.shiftEast(bitboard), 0x800);
	EXPECT_EQ(generator.shiftSouthEast(bitboard), 0x08);
	EXPECT_EQ(generator.shiftSouth(bitboard), 0x04);
	EXPECT_EQ(generator.shiftSouthWest(bitboard), 0x02);
	EXPECT_EQ(generator.shiftWest(bitboard), 0x200);
	EXPECT_EQ(generator.shiftNorthWest(bitboard), 0x20000);

}

