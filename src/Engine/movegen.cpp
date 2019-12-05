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
	return bitboard << 7 & notHFile;
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
	return bitboard << 9 & notAFile;
}

/**
 * @details shifts bitboard east. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 1
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftEast(U64 bitboard) {
	return bitboard << 1 & notAFile;
}

/**
 * @details shifts bitboard southeast. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 1
 */
U64 MoveGenerator::shiftSouthEast(U64 bitboard) {
	return bitboard >> 7 & notAFile;
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
	return bitboard >> 9 & notHFile;
}

/**
 * @details shifts bitboard west. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 1 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftWest(U64 bitboard) {
	return bitboard >> 1 & notHFile;
}

/**
 * @details Returns a bitboard with all pseudo-legal moves for a given color of pawn pieces.
 * @todo Currently its only possible to move one file up. Implement the possibility to move two files up on the first move.
 */
U64 MoveGenerator::getPawnMoves(const U64 *bitboard, pieceColor color) {
	if (color == pieceColor::nWhite) {
		U64 pawns = bitboard[pieceType::nPawn] & bitboard[pieceColor::nWhite];		// every white pawn on the board

		U64 attacks = shiftNorthEast(pawns) | shiftNorthWest(pawns);				// theoretical possible attacks
		attacks &= bitboard[pieceColor::nBlack];									// real possible attacks (it's only possible to attack if there is a enemy piece)

		U64 moves = shiftNorth(pawns);
		//moves &= ~bitboard[pieceColor::nColor];									// can't move if there is a piece blocking the way

		return attacks | moves;														// pseudo-legal moves (capture and move)
	}
	else if (color == pieceColor::nBlack){
		U64 pawns = bitboard[pieceType::nPawn] & bitboard[pieceColor::nBlack];

		U64 attacks = shiftSouthWest(pawns) | shiftSouthEast(pawns);
		attacks &= bitboard[pieceColor::nWhite];

		U64 moves = shiftSouth(pawns);
		//moves &= ~bitboard[pieceColor::nColor];

		return attacks | moves;
	}
	else
		return getPawnMoves(bitboard, pieceColor::nBlack) | getPawnMoves(bitboard, pieceColor::nWhite);
}

/**
 * @details Returns a bitboard with all pseudo-legal moves for a given king. "Moves" the king in every direction and checks for collisions. Return the moves that do not collide with pieces of the same color.
 * @todo Implement castle as a pseudo-legal move?
 */
U64 MoveGenerator::getKingMoves(const U64 *bitboard, pieceColor color) {
	U64 king = bitboard[pieceType::nKing] & bitboard[color];

	U64 moves = shiftNorth(king) | shiftNorthEast(king) | shiftEast(king) | shiftSouthEast(king) | shiftSouth(king) | shiftSouthWest(king) | shiftWest(king) | shiftNorthWest(king);
	U64 validSquares = ~bitboard[color];

	return moves & validSquares;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for knights of a given color.
 * Every possible theoretical move is accounted for, but only the ones that do not collide with allied pieces are returned.
 */
U64 MoveGenerator::getKnightMoves(const U64 *bitboard, chessqdl::pieceColor color) {
	U64 knights = bitboard[pieceType::nKnight] & bitboard[color];

	U64 WWN = shiftNorthWest(shiftWest(knights));			// west west north
	U64 WNN = shiftNorthWest(shiftNorth(knights));			// west north north
	U64 ENN = shiftNorthEast(shiftNorth(knights));  		// east north north
	U64 EEN = shiftNorthEast(shiftEast(knights));			// east east north

	U64 EES = shiftSouthEast(shiftEast(knights));			// east east south
	U64 ESS = shiftSouthEast(shiftSouth(knights));			// east south south
	U64 WSS = shiftSouthWest(shiftSouth(knights));		    // west south south
	U64 WWS = shiftSouthWest(shiftWest(knights));			// west west south

	U64 moves =  WWN | WNN | ENN | EEN | EES | ESS | WSS | WWS;

	if (color == pieceColor::nColor)
	    return getKnightMoves(bitboard, pieceColor::nBlack) | getKnightMoves(bitboard, pieceColor::nWhite);

    U64 notAlly = ~bitboard[color];

    return moves & notAlly;								// moves and every square that doesn't contain an piece of the same color
}


