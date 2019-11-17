#include "movegen.h"

using namespace chessqdl;

/**
 * @details shifts bitboard northwest. E.g
 * 0 0 0	1 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthWest(U64 bitboard) {
	return bitboard << 7;
}

/**
 * @details shifts bitboard north. E.g
 * 0 0 0	0 1 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorth(U64 bitboard) {
	return bitboard << 8;
}

/**
 * @details shifts bitboard northeast. E.g
 * 0 0 0	0 0 1
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthEast(U64 bitboard) {
	return bitboard << 9;
}

/**
 * @details shifts bitboard east. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 1
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftEast(U64 bitboard) {
	return bitboard << 1;
}

/**
 * @details shifts bitboard southeast. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 1
 */
U64 MoveGenerator::shiftSouthEast(U64 bitboard) {
	return bitboard >> 7;
}

/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 1 0
 */
U64 MoveGenerator::shiftSouth(U64 bitboard) {
	return bitboard >> 8;
}

/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	1 0 0
 */
U64 MoveGenerator::shiftSouthWest(U64 bitboard) {
	return bitboard >> 9;
}

/**
 * @details shifts bitboard west. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 1 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftWest(U64 bitboard) {
	return bitboard >> 1;
}
