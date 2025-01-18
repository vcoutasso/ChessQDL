#include "movegen.hpp"
#include "utils.hpp"


using namespace chessqdl;


/**
 * @details shifts bitboard northwest. E.g
 * 0 0 0	1 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthWest(const U64 bitboard) {
	return (bitboard << noWe) & notHFile;
}


/**
 * @details shifts bitboard north. E.g
 * 0 0 0	0 1 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorth(const U64 bitboard) {
	return bitboard << nort;
}


/**
 * @details shifts bitboard northeast. E.g
 * 0 0 0	0 0 1
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftNorthEast(const U64 bitboard) {
	return (bitboard << noEa) & notAFile;
}


/**
 * @details shifts bitboard east. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 1
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftEast(const U64 bitboard) {
	return (bitboard << east) & notAFile;
}


/**
 * @details shifts bitboard southeast. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 0 1
 */
U64 MoveGenerator::shiftSouthEast(const U64 bitboard) {
	return (bitboard >> -soEa) & notAFile;
}


/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	0 1 0
 */
U64 MoveGenerator::shiftSouth(const U64 bitboard) {
	return bitboard >> -sout;
}


/**
 * @details shifts bitboard south. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 0 0 0
 * 0 0 0	1 0 0
 */
U64 MoveGenerator::shiftSouthWest(const U64 bitboard) {
	return (bitboard >> -soWe) & notHFile;
}


/**
 * @details shifts bitboard west. E.g
 * 0 0 0	0 0 0
 * 0 1 0 -> 1 0 0
 * 0 0 0	0 0 0
 */
U64 MoveGenerator::shiftWest(const U64 bitboard) {
	return (bitboard >> -west) & notHFile;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soutOccl(U64 generator, U64 propagator) {
	generator |= propagator & (generator >> 8);
	propagator &= (propagator >> 8);
	generator |= propagator & (generator >> 16);
	propagator &= (propagator >> 16);
	generator |= propagator & (generator >> 32);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::nortOccl(U64 generator, U64 propagator) {
	generator |= propagator & (generator << 8);
	propagator &= (propagator << 8);
	generator |= propagator & (generator << 16);
	propagator &= (propagator << 16);
	generator |= propagator & (generator << 32);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::eastOccl(U64 generator, U64 propagator) {
	propagator &= notAFile;
	generator |= propagator & (generator << 1);
	propagator &= (propagator << 1);
	generator |= propagator & (generator << 2);
	propagator &= (propagator << 2);
	generator |= propagator & (generator << 4);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::noEaOccl(U64 generator, U64 propagator) {
	propagator &= notAFile;
	generator |= propagator & (generator << 9);
	propagator &= (propagator << 9);
	generator |= propagator & (generator << 18);
	propagator &= (propagator << 18);
	generator |= propagator & (generator << 36);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soEaOccl(U64 generator, U64 propagator) {
	propagator &= notAFile;
	generator |= propagator & (generator >> 7);
	propagator &= (propagator >> 7);
	generator |= propagator & (generator >> 14);
	propagator &= (propagator >> 14);
	generator |= propagator & (generator >> 28);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::westOccl(U64 generator, U64 propagator) {
	propagator &= notHFile;
	generator |= propagator & (generator >> 1);
	propagator &= (propagator >> 1);
	generator |= propagator & (generator >> 2);
	propagator &= (propagator >> 2);
	generator |= propagator & (generator >> 4);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::soWeOccl(U64 generator, U64 propagator) {
	propagator &= notHFile;
	generator |= propagator & (generator >> 9);
	propagator &= (propagator >> 9);
	generator |= propagator & (generator >> 18);
	propagator &= (propagator >> 18);
	generator |= propagator & (generator >> 36);
	return generator;
}


/**
 * @details The following private methods are part of the Kogge-Stone algorithm for sliding pieces move generation
 * @ref https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */
U64 MoveGenerator::noWeOccl(U64 generator, U64 propagator) {
	propagator &= notHFile;
	generator |= propagator & (generator << 7);
	propagator &= (propagator << 7);
	generator |= propagator & (generator << 14);
	propagator &= (propagator << 14);
	generator |= propagator & (generator << 28);
	return generator;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for a given color of pawn pieces.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getPawnMoves(const BitboardArray &bitboard, const enumColor color) {
	if (color == nWhite) {
		const U64 pawns = bitboard[nPawn] & bitboard[nWhite];        // every white pawn on the board

		U64 attacks = shiftNorthEast(pawns) | shiftNorthWest(pawns);                // theoretical possible attacks
		attacks &= bitboard[nBlack];                                    // real possible attacks (it's only possible to attack if there is an enemy piece)

		U64 moves = shiftNorth(pawns);
		moves &= ~bitboard[nColor];                                    // can't move if there is a piece blocking the way

		// If pawn is on its initial position, give the possibility to "move twice"
		U64 aux = moves;
		aux = aux << 40;
		aux = aux >> 56;
		aux = aux << 16;

		moves |= shiftNorth(aux);
		moves &= ~bitboard[nColor];

		return attacks | moves;														// pseudo-legal moves (capture and move)

	} else if (color == nBlack) {
		const U64 pawns = bitboard[nPawn] & bitboard[nBlack];

		U64 attacks = shiftSouthWest(pawns) | shiftSouthEast(pawns);
		attacks &= bitboard[nWhite];

		U64 moves = shiftSouth(pawns);
		moves &= ~bitboard[nColor];

		// If pawn is on its initial position, give the possibility to "move twice"
		U64 aux = moves;
		aux = aux << 16;
		aux = aux >> 56;
		aux = aux << 40;

		moves |= shiftSouth(aux);
		moves &= ~bitboard[nColor];

		return attacks | moves;
	}
	else
		return getPawnMoves(bitboard, nBlack) | getPawnMoves(bitboard, nWhite);
}
// NOLINTEND(misc-no-recursion)


/**
 * @details Returns a bitboard with all pseudo-legal moves for a given king. "Moves" the king in every direction and checks for collisions. Return the moves that do not collide with pieces of the same color.
 * @todo Implement castle as a pseudo-legal move?
 */
U64 MoveGenerator::getKingMoves(const BitboardArray &bitboard, const enumColor color) {
	const U64 king = bitboard[nKing] & bitboard[color];

	const U64 moves = shiftNorth(king) | shiftNorthEast(king) | shiftEast(king) | shiftSouthEast(king) | shiftSouth(king) | shiftSouthWest(king) | shiftWest(king) | shiftNorthWest(king);
	const U64 validSquares = ~bitboard[color];

	return moves & validSquares;
}


/**
 * @details Returns a bitboard with all pseudo-legal moves for knights of a given color.
 * Every possible theoretical move is accounted for, but only the ones that do not collide with allied pieces are returned.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getKnightMoves(const BitboardArray &bitboard, const enumColor color) {
	const U64 knights = bitboard[nKnight] & bitboard[color];

	if (color == nColor)
		return getKnightMoves(bitboard, nBlack) | getKnightMoves(bitboard, nWhite);

	const U64 WWN = shiftNorthWest(shiftWest(knights));            // west-west-north
	const U64 WNN = shiftNorthWest(shiftNorth(knights));            // west-north-north
	const U64 ENN = shiftNorthEast(shiftNorth(knights));        // east-north-north
	const U64 EEN = shiftNorthEast(shiftEast(knights));            // east-east-north

	const U64 EES = shiftSouthEast(shiftEast(knights));			// east-east-south
	const U64 ESS = shiftSouthEast(shiftSouth(knights));			// east-south-south
	const U64 WSS = shiftSouthWest(shiftSouth(knights));		    // west-south-south
	const U64 WWS = shiftSouthWest(shiftWest(knights));			// west-west-south

	const U64 moves =  WWN | WNN | ENN | EEN | EES | ESS | WSS | WWS;

    const U64 notAlly = ~bitboard[color];

    return moves & notAlly;								// moves and every square that doesn't contain a piece of the same color
}

// NOLINTEND(misc-no-recursion)

/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getBishopMoves(const BitboardArray &bitboard, const enumColor color, const enumPiece piece) {
	const U64 bishops = bitboard[piece] & bitboard[color];
	const U64 empty = ~bitboard[nColor];

	if (color == nColor)
		return getBishopMoves(bitboard, nWhite, piece) | getBishopMoves(bitboard, nBlack, piece);

	const U64 noEaOcc = noEaOccl(bishops, empty);
	const U64 soEaOcc = soEaOccl(bishops, empty);
	const U64 noWeOcc = noWeOccl(bishops, empty);
	const U64 soWeOcc = soWeOccl(bishops, empty);

	const U64 noEaAttacks = shiftNorthEast(noEaOcc);
	const U64 soEaAttacks = shiftSouthEast(soEaOcc);
	const U64 noWeAttacks = shiftNorthWest(noWeOcc);
	const U64 soWeAttacks = shiftSouthWest(soWeOcc);

	U64 attacks = noEaAttacks | soEaAttacks | noWeAttacks | soWeAttacks;
	attacks &= ~bitboard[color]; // Attacks are only valid if the piece is an enemy piece
	U64 moves = noEaOcc | soEaOcc | noWeOcc | soWeOcc;
	moves &= ~bitboard[piece]; // "Moving" without leaving the square is invalid

	return moves | attacks;
}
// NOLINTEND(misc-no-recursion)

/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getRookMoves(const BitboardArray &bitboard, const enumColor color, const enumPiece piece) {
	const U64 rooks = bitboard[piece] & bitboard[color];
	const U64 empty = ~bitboard[nColor];

	if (color == nColor)
		return getRookMoves(bitboard, nWhite, piece) | getRookMoves(bitboard, nBlack, piece);

	const U64 soutOcc = soutOccl(rooks, empty);
	const U64 nortOcc = nortOccl(rooks, empty);
	const U64 eastOcc = eastOccl(rooks, empty);
	const U64 westOcc = westOccl(rooks, empty);

	const U64 soutAttacks = shiftSouth(soutOcc);
	const U64 nortAttacks = shiftNorth(nortOcc);
	const U64 eastAttacks = shiftEast(eastOcc);
	const U64 westAttacks = shiftWest(westOcc);

	U64 attacks = soutAttacks | nortAttacks | eastAttacks | westAttacks;
	attacks &= ~bitboard[color]; // Attacks are only valid if the piece is an enemy piece
	U64 moves = soutOcc | nortOcc | eastOcc | westOcc;
	moves &= ~bitboard[piece]; // "Moving" without leaving the square is invalid

	return moves | attacks;
}
// NOLINTEND(misc-no-recursion)


/**
 * @details Makes use of the implementation of bishop and rooks move generation.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getQueenMoves(const BitboardArray &bitboard, const enumColor color) {
	if (color == nColor)
		return getQueenMoves(bitboard, nWhite) | getQueenMoves(bitboard, nBlack);

	return getBishopMoves(bitboard, color, nQueen) | getRookMoves(bitboard, color, nQueen);
}
// NOLINTEND(misc-no-recursion)

/**
 * @details Identifies all pawns that can promote on next move and generates a list with all possible promotions. Also removes the option to just move without promoting
 */
std::vector<std::string> MoveGenerator::getPawnPromotions(U64 &pawnMoves, const uint64_t fromPos) {
	const U64 whitePromotions = pawnMoves & U64(0xffL << 56); // White pawn moves that are promotions
	const U64 blackPromotions = pawnMoves & U64(0xffL); // Black pawn moves that are promotions

	// Removes the promoting pawns from standard moves
	pawnMoves ^= whitePromotions;
	pawnMoves ^= blackPromotions;

	// Promotions as uint64_t
	uint64_t uWhitePromotions = whitePromotions.to_ullong();
	uint64_t uBlackPromotions = blackPromotions.to_ullong();

	int i;
	uint64_t toPos;
	std::string move;
	std::vector<std::string> promotions;

	while (uWhitePromotions) {
		i = leastSignificantSetBit(uWhitePromotions);
		toPos = 1L << i;
		uWhitePromotions ^= toPos;
		move = moveName(fromPos, toPos);
		promotions.push_back(move + "n"); // Promote to Knight
		promotions.push_back(move + "b"); // Promote to Bishop
		promotions.push_back(move + "r"); // Promote to Rook
		promotions.push_back(move + "q"); // Promote to Queen
	}

	while (uBlackPromotions) {
		i = leastSignificantSetBit(uBlackPromotions);
		toPos = 1l << i;
		uBlackPromotions ^= toPos;
		move = moveName(fromPos, toPos);
		promotions.push_back(move + "n"); // Promote to Knight
		promotions.push_back(move + "b"); // Promote to Bishop
		promotions.push_back(move + "r"); // Promote to Rook
		promotions.push_back(move + "q"); // Promote to Queen
	}

	return promotions;
}


/**
 * @details Iterates through all bitboards (from nPawn to nKing) generating moves for pieces one at a time. If there are 16 pawns on the board, this method will generate pawn moves 16 times, one for each individual pawn.
 * It does so for every type of piece on the board, and then returns a list with strings of all possible moves it has found.
 */
// NOLINTBEGIN(misc-no-recursion)
std::vector<std::string> MoveGenerator::getPseudoLegalMoves(const BitboardArray &bitboard, const enumColor color) {
	if (color == nColor) {
		std::vector<std::string> white = getPseudoLegalMoves(bitboard, nWhite);
		std::vector<std::string> black = getPseudoLegalMoves(bitboard, nBlack);

		// Concatenates both lists (inserts the black list on the end of white list)
		white.insert(white.end(), black.begin(), black.end());

		return white;
	}

	std::vector<std::string> moves;
	std::vector<std::string> promotions;

	BitboardArray bitboardCopy = bitboard;

	for (int k = nPawn; k <= nKing; k++) {

		U64 pieces = bitboard[k];
		pieces &= bitboard[color];

		U64 pieceMoves;

		uint64_t upieces = pieces.to_ullong();

		while (upieces) {
			// Get index of the least significant set bit
			const int i = leastSignificantSetBit(upieces);
			upieces ^= (1L << i); // Reset bit

			bitboardCopy[k].reset();
			bitboardCopy[k].set(i);

			const uint64_t fromPos = 1L << i; // Original position

			switch (k) {
				case nPawn:
					pieceMoves = getPawnMoves(bitboardCopy, color);
					promotions = getPawnPromotions(pieceMoves, fromPos);
					if (!promotions.empty()) {
						moves.insert(moves.end(), promotions.begin(), promotions.end());
					}
					break;

				case nKnight:
					pieceMoves = getKnightMoves(bitboardCopy, color);
					break;

				case nBishop:
					pieceMoves = getBishopMoves(bitboardCopy, color);
					break;

				case nRook:
					pieceMoves = getRookMoves(bitboardCopy, color);
					break;

				case nQueen:
					pieceMoves = getQueenMoves(bitboardCopy, color);
					break;

				case nKing:
					pieceMoves = getKingMoves(bitboardCopy, color);
					break;

				default:
					break;
			}

			uint64_t umoves = pieceMoves.to_ullong();

			// Loops through all possible moves that the piece of type `k` at the `i` position can make and adds it to the list of moves
			while (umoves) {
				int j = leastSignificantSetBit(umoves);
				umoves ^= (1L << j); // Reset bit
				const uint64_t toPos = 1L << j; // Target position

				moves.push_back(moveName(fromPos, toPos));
			}
		}
	}

	return moves;
}
// NOLINTEND(misc-no-recursion)
