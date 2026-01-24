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
U64 MoveGenerator::getPawnMoves(const BitboardArray &bitboard, const enumColor color, int enPassantSquare, const BitboardArray* originalBitboard) {
    if (color == nColor) return getPawnMoves(bitboard, nBlack, enPassantSquare, originalBitboard) | getPawnMoves(bitboard, nWhite, enPassantSquare, originalBitboard);

    const enumColor opponentColor = color == nWhite ? nBlack : nWhite;
    const U64 pawn = bitboard[nPawn] & bitboard[color];
    const U64 initialPawns = pawn & U64(0xffL << (color == nWhite ? 8 : 48));
    
    // Single pawn moves
    const U64 singleMoves = color == nWhite ? shiftNorth(pawn) : shiftSouth(pawn);
    const U64 validSingleMoves = singleMoves & ~bitboard[nColor];
    
    // Double moves: only from initial position and only if both squares are empty
    // Find pawns on starting rank whose single-move destination is empty (can advance one square)
    const U64 doubleMovesPawns = initialPawns & (color == nWhite 
                                                     ? shiftSouth(validSingleMoves)
                                                     : shiftNorth(validSingleMoves));
    const U64 doubleMoveSquares = color == nWhite
                                ? shiftNorth(shiftNorth(doubleMovesPawns))
                                : shiftSouth(shiftSouth(doubleMovesPawns));
    const U64 validDoubleMoves = doubleMoveSquares & ~bitboard[nColor];
    
    const U64 attacks = bitboard[opponentColor] & (color == nWhite
                                                       ? shiftNorthEast(pawn) | shiftNorthWest(pawn)
                                                       : shiftSouthEast(pawn) | shiftSouthWest(pawn));

    // En passant captures  
    // The en passant target square in FEN indicates where the opponent's pawn passed through.
    // The capturing pawn moves diagonally TO the en passant square.
    //
    // Example: White pawn moves e2→e4, en passant square is e3
    // - Black pawn on d4 or f4 can capture by moving diagonally to e3
    // - The white pawn at e4 (one rank NORTH of e3) is removed
    U64 enPassantMoves = 0UL;
    if (enPassantSquare > 0 && originalBitboard != nullptr) {
        U64 epTargetSquare = U64().reset();
        epTargetSquare.set(enPassantSquare);
        
        // Check if there's actually an opponent pawn adjacent to the en passant square
        // The opponent pawn is one rank AWAY from the en passant square
        // For white capturing: opponent pawn is SOUTH (one rank down) from ep square
        // For black capturing: opponent pawn is NORTH (one rank up) from ep square
        U64 opponentPawnSquare;
        if (color == nWhite) {
            // White captures: opponent pawn is south of ep square
            opponentPawnSquare = shiftSouth(epTargetSquare);
        } else {
            // Black captures: opponent pawn is north of ep square  
            opponentPawnSquare = shiftNorth(epTargetSquare);
        }
        
        // Only valid if there's an opponent pawn at the calculated square (check original bitboard!)
        if ((opponentPawnSquare & (*originalBitboard)[nPawn] & (*originalBitboard)[opponentColor]).any()) {
            if (color == nWhite) {
                // White pawn can move to ep square if it can attack there diagonally
                // A white pawn at d4 attacks diagonally NW and NE to c5 and e5
                // So to reach ep square e3, we need pawns at shiftSouthWest(e3) or shiftSouthEast(e3)
                U64 attackersFromWest = shiftSouthWest(epTargetSquare) & pawn;
                U64 attackersFromEast = shiftSouthEast(epTargetSquare) & pawn;
                if ((attackersFromWest | attackersFromEast).any()) {
                    enPassantMoves = epTargetSquare;
                }
            } else {
                // Black pawn can move to ep square if it can attack there diagonally
                // A black pawn at d5 attacks diagonally SW and SE to c4 and e4
                // So to reach ep square e6, we need pawns at shiftNorthWest(e6) or shiftNorthEast(e6)
                U64 attackersFromWest = shiftNorthWest(epTargetSquare) & pawn;
                U64 attackersFromEast = shiftNorthEast(epTargetSquare) & pawn;
                if ((attackersFromWest | attackersFromEast).any()) {
                    enPassantMoves = epTargetSquare;
                }
            }
        }
    }

    return (validSingleMoves | validDoubleMoves) | attacks | enPassantMoves;
}
// NOLINTEND(misc-no-recursion)


/**
 * @details Returns a bitboard with all pseudo-legal moves for a given king. "Moves" the king in every direction and checks for collisions. Return the moves that do not collide with pieces of the same color.
 * @todo Implement castle as a pseudo-legal move?
 */
U64 MoveGenerator::getKingMoves(const BitboardArray &bitboard, const enumColor color) {
    const U64 king = bitboard[nKing] & bitboard[color];

    const U64 moves = shiftNorth(king) | shiftNorthEast(king) | shiftEast(king) | shiftSouthEast(king) |
                      shiftSouth(king) | shiftSouthWest(king) | shiftWest(king) | shiftNorthWest(king);
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

    const U64 WWN = shiftNorthWest(shiftWest(knights)); // west-west-north
    const U64 WNN = shiftNorthWest(shiftNorth(knights)); // west-north-north
    const U64 ENN = shiftNorthEast(shiftNorth(knights)); // east-north-north
    const U64 EEN = shiftNorthEast(shiftEast(knights)); // east-east-north

    const U64 EES = shiftSouthEast(shiftEast(knights)); // east-east-south
    const U64 ESS = shiftSouthEast(shiftSouth(knights)); // east-south-south
    const U64 WSS = shiftSouthWest(shiftSouth(knights)); // west-south-south
    const U64 WWS = shiftSouthWest(shiftWest(knights)); // west-west-south

    const U64 moves = WWN | WNN | ENN | EEN | EES | ESS | WSS | WWS;

    const U64 notAlly = ~bitboard[color];

    return moves & notAlly; // moves and every square that doesn't contain a piece of the same color
}

// NOLINTEND(misc-no-recursion)

/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getBishopMoves(const BitboardArray &bitboard, const enumColor color, const enumPiece piece) {
    const U64 bishop = bitboard[piece] & bitboard[color];
    const U64 empty = ~bitboard[nColor];

    if (color == nColor)
        return getBishopMoves(bitboard, nWhite, piece) | getBishopMoves(bitboard, nBlack, piece);

    // Occluded fills include sliders but exclude blockers
    const U64 noEaOcc = noEaOccl(bishop, empty);
    const U64 soEaOcc = soEaOccl(bishop, empty);
    const U64 noWeOcc = noWeOccl(bishop, empty);
    const U64 soWeOcc = soWeOccl(bishop, empty);

    // Perform an additional shift to consider possible captures
    const U64 noEaAttacks = shiftNorthEast(noEaOcc);
    const U64 soEaAttacks = shiftSouthEast(soEaOcc);
    const U64 noWeAttacks = shiftNorthWest(noWeOcc);
    const U64 soWeAttacks = shiftSouthWest(soWeOcc);

    U64 moves = noEaOcc | soEaOcc | noWeOcc | soWeOcc;
    moves &= ~bishop; // "Moving" without leaving the square is invalid
    U64 attacks = noEaAttacks | soEaAttacks | noWeAttacks | soWeAttacks;
    attacks &= bitboard[(color == nWhite) ? nBlack : nWhite];

    return moves | attacks;
}

// NOLINTEND(misc-no-recursion)

/**
 * @details Gets occluded fills for every direction for the possible moves (excludes blockers). For the attacks, the occluded fills need to be shifted one further.
 */
// NOLINTBEGIN(misc-no-recursion)
U64 MoveGenerator::getRookMoves(const BitboardArray &bitboard, const enumColor color, const enumPiece piece) {
    const U64 rook = bitboard[piece] & bitboard[color];
    const U64 empty = ~bitboard[nColor];

    if (color == nColor)
        return getRookMoves(bitboard, nWhite, piece) | getRookMoves(bitboard, nBlack, piece);

    // Occluded fills include sliders but exclude blockers
    const U64 soutOcc = soutOccl(rook, empty);
    const U64 nortOcc = nortOccl(rook, empty);
    const U64 eastOcc = eastOccl(rook, empty);
    const U64 westOcc = westOccl(rook, empty);

    // Perform an additional shift to consider possible captures
    const U64 soutAttacks = shiftSouth(soutOcc);
    const U64 nortAttacks = shiftNorth(nortOcc);
    const U64 eastAttacks = shiftEast(eastOcc);
    const U64 westAttacks = shiftWest(westOcc);

    U64 moves = soutOcc | nortOcc | eastOcc | westOcc;
    moves &= ~rook; // "Moving" without leaving the square is invalid
    U64 attacks = soutAttacks | nortAttacks | eastAttacks | westAttacks;
    attacks &= bitboard[(color == nWhite) ? nBlack : nWhite];

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
 * @details Check if a square is attacked by the opponent
 */
bool MoveGenerator::isSquareAttacked(const BitboardArray &bitboard, int square, enumColor attackerColor) {
    U64 squareBB;
    squareBB.set(square);
    
    // Check attacks from all piece types
    U64 attacks = getBishopMoves(bitboard, attackerColor) |
                  getRookMoves(bitboard, attackerColor) |
                  getKnightMoves(bitboard, attackerColor) |
                  getPawnMoves(bitboard, attackerColor, 0) |
                  getQueenMoves(bitboard, attackerColor) |
                  getKingMoves(bitboard, attackerColor);
    
    return (squareBB & attacks).any();
}


/**
 * @details Generates castling moves if they are legal.
 * Castling requirements:
 * 1. King and rook haven't moved (tracked by castling rights)
 * 2. No pieces between king and rook
 * 3. King is not in check
 * 4. King doesn't pass through or end up on an attacked square
 */
std::vector<std::string> MoveGenerator::getCastlingMoves(const BitboardArray &bitboard, enumColor color, int castlingRights) {
    std::vector<std::string> moves;
    
    if (castlingRights == 0) return moves;
    
    const enumColor opponentColor = (color == nWhite) ? nBlack : nWhite;
    const U64 allPieces = bitboard[nColor];
    
    // Kingside castling
    bool canCastleKingside = (color == nWhite) ? (castlingRights & 0b0001) : (castlingRights & 0b0100);
    // Queenside castling  
    bool canCastleQueenside = (color == nWhite) ? (castlingRights & 0b0010) : (castlingRights & 0b1000);
    
    if (color == nWhite) {
        // White kingside: e1-g1, rook h1-f1
        // Squares f1 and g1 must be empty, king passes through f1 to g1
        if (canCastleKingside) {
            // Check squares between king (e1=4) and rook (h1=7) are empty: f1=5, g1=6
            bool pathClear = !allPieces.test(f1) && !allPieces.test(g1);
            // King must not be in check, and must not pass through or land on attacked square
            bool kingNotInCheck = !isSquareAttacked(bitboard, e1, opponentColor);
            bool pathNotAttacked = !isSquareAttacked(bitboard, f1, opponentColor) && 
                                   !isSquareAttacked(bitboard, g1, opponentColor);
            if (pathClear && kingNotInCheck && pathNotAttacked) {
                moves.push_back("e1g1");
            }
        }
        
        // White queenside: e1-c1, rook a1-d1
        // Squares b1, c1, d1 must be empty (rook passes through b1), king passes through d1 to c1
        if (canCastleQueenside) {
            bool pathClear = !allPieces.test(b1) && !allPieces.test(c1) && !allPieces.test(d1);
            bool kingNotInCheck = !isSquareAttacked(bitboard, e1, opponentColor);
            bool pathNotAttacked = !isSquareAttacked(bitboard, d1, opponentColor) && 
                                   !isSquareAttacked(bitboard, c1, opponentColor);
            if (pathClear && kingNotInCheck && pathNotAttacked) {
                moves.push_back("e1c1");
            }
        }
    } else {
        // Black kingside: e8-g8, rook h8-f8
        if (canCastleKingside) {
            bool pathClear = !allPieces.test(f8) && !allPieces.test(g8);
            bool kingNotInCheck = !isSquareAttacked(bitboard, e8, opponentColor);
            bool pathNotAttacked = !isSquareAttacked(bitboard, f8, opponentColor) && 
                                   !isSquareAttacked(bitboard, g8, opponentColor);
            if (pathClear && kingNotInCheck && pathNotAttacked) {
                moves.push_back("e8g8");
            }
        }
        
        // Black queenside: e8-c8, rook a8-d8
        if (canCastleQueenside) {
            bool pathClear = !allPieces.test(b8) && !allPieces.test(c8) && !allPieces.test(d8);
            bool kingNotInCheck = !isSquareAttacked(bitboard, e8, opponentColor);
            bool pathNotAttacked = !isSquareAttacked(bitboard, d8, opponentColor) && 
                                   !isSquareAttacked(bitboard, c8, opponentColor);
            if (pathClear && kingNotInCheck && pathNotAttacked) {
                moves.push_back("e8c8");
            }
        }
    }
    
    return moves;
}


/**
 * @details Iterates through all bitboards (from nPawn to nKing) generating moves for pieces one at a time. If there are 16 pawns on the board, this method will generate pawn moves 16 times, one for each individual pawn.
 * It does so for every type of piece on the board, and then returns a list with strings of all possible moves it has found.
 */
// NOLINTBEGIN(misc-no-recursion)
std::vector<std::string> MoveGenerator::getPseudoLegalMoves(const BitboardArray &bitboard, const enumColor color, int enPassantSquare, int castlingRights) {
    if (color == nColor) {
        std::vector<std::string> white = getPseudoLegalMoves(bitboard, nWhite, enPassantSquare, castlingRights);
        std::vector<std::string> black = getPseudoLegalMoves(bitboard, nBlack, enPassantSquare, castlingRights);

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
                    pieceMoves = getPawnMoves(bitboardCopy, color, enPassantSquare, &bitboard);
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

    // Add castling moves
    std::vector<std::string> castlingMoves = getCastlingMoves(bitboard, color, castlingRights);
    moves.insert(moves.end(), castlingMoves.begin(), castlingMoves.end());

    return moves;
}

// NOLINTEND(misc-no-recursion)
