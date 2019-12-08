#include "movegen.h"
#include "bitboard.h"
#include <iostream>

using namespace chessqdl;

/**
 * @details shifts bitboard northwest. E.g
 * 0 0 0	1 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthWest(U64 bitboard) {
	return bitboard << noWe & notHFile;
}

/**
 * @details shifts bitboard north. E.g
 * 0 0 0	0 1 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorth(U64 bitboard) {
	return bitboard << nort;
}

/**
 * @details shifts bitboard northeast. E.g
 * 0 0 0	0 0 1
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthEast(U64 bitboard) {
	return bitboard << noEa & notAFile;
}

/**
 * @details shifts bitboard east. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 1
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftEast(U64 bitboard) {
	return bitboard << east & notAFile;
}

/**
 * @details shifts bitboard southeast. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 1
 */
U64 MoveGenerator::shiftSouthEast(U64 bitboard) {
	return bitboard >> -soEa & notAFile;
}

/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 1 0
 */
U64 MoveGenerator::shiftSouth(U64 bitboard) {
	return bitboard >> -sout;
}

/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	1 0 0
 */
U64 MoveGenerator::shiftSouthWest(U64 bitboard) {
	return bitboard >> -soWe & notHFile;
}

/**
 * @details shifts bitboard west. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 1 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftWest(U64 bitboard) {
	return bitboard >> -west & notHFile;
}

/**
 * @details Returns a bitboard with all pseudo-legal moves for a given color of pawn pieces.
 * @todo Currently its only possible to move one file up. Implement the possibility to move two files up on the first move.
 */
U64 MoveGenerator::getPawnMoves(const U64 *bitboard, enumColor color) {
	if (color == enumColor::nWhite) {
		U64 pawns = bitboard[enumType::nPawn] & bitboard[enumColor::nWhite];        // every white pawn on the board

		U64 attacks = shiftNorthEast(pawns) | shiftNorthWest(pawns);				// theoretical possible attacks
		attacks &= bitboard[enumColor::nBlack];                                    // real possible attacks (it's only possible to attack if there is a enemy piece)

		U64 moves = shiftNorth(pawns);
		//moves &= ~bitboard[enumColor::nColor];									// can't move if there is a piece blocking the way

		return attacks | moves;														// pseudo-legal moves (capture and move)
	} else if (color == enumColor::nBlack) {
		U64 pawns = bitboard[enumType::nPawn] & bitboard[enumColor::nBlack];

		U64 attacks = shiftSouthWest(pawns) | shiftSouthEast(pawns);
		attacks &= bitboard[enumColor::nWhite];

		U64 moves = shiftSouth(pawns);
		//moves &= ~bitboard[enumColor::nColor];

		return attacks | moves;
	}
	else
		return getPawnMoves(bitboard, enumColor::nBlack) | getPawnMoves(bitboard, enumColor::nWhite);
}

/**
 * @details Returns a bitboard with all pseudo-legal moves for a given king. "Moves" the king in every direction and checks for collisions. Return the moves that do not collide with pieces of the same color.
 * @todo Implement castle as a pseudo-legal move?
 */
U64 MoveGenerator::getKingMoves(const U64 *bitboard, enumColor color) {
	U64 king = bitboard[enumType::nKing] & bitboard[color];

	U64 moves = shiftNorth(king) | shiftNorthEast(king) | shiftEast(king) | shiftSouthEast(king) | shiftSouth(king) | shiftSouthWest(king) | shiftWest(king) | shiftNorthWest(king);
	U64 validSquares = ~bitboard[color];

	return moves & validSquares;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for knights of a given color.
 * Every possible theoretical move is accounted for, but only the ones that do not collide with allied pieces are returned.
 */
U64 MoveGenerator::getKnightMoves(const U64 *bitboard, chessqdl::enumColor color) {
	U64 knights = bitboard[enumType::nKnight] & bitboard[color];

	U64 WWN = shiftNorthWest(shiftWest(knights));			// west west north
	U64 WNN = shiftNorthWest(shiftNorth(knights));			// west north north
	U64 ENN = shiftNorthEast(shiftNorth(knights));  		// east north north
	U64 EEN = shiftNorthEast(shiftEast(knights));			// east east north

	U64 EES = shiftSouthEast(shiftEast(knights));			// east east south
	U64 ESS = shiftSouthEast(shiftSouth(knights));			// east south south
	U64 WSS = shiftSouthWest(shiftSouth(knights));		    // west south south
	U64 WWS = shiftSouthWest(shiftWest(knights));			// west west south

	U64 moves =  WWN | WNN | ENN | EEN | EES | ESS | WSS | WWS;

	if (color == enumColor::nColor)
		return getKnightMoves(bitboard, enumColor::nBlack) | getKnightMoves(bitboard, enumColor::nWhite);

    U64 notAlly = ~bitboard[color];

    return moves & notAlly;								// moves and every square that doesn't contain an piece of the same color
}


