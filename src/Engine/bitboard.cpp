#include "bitboard.h"
#include "const.h"

#include <string>
#include <iostream>
#include <cctype>

using namespace chessqdl;

/* TODO: Implement a method that receives a fen string as parameter to initialize bitboards */

/**
 * @details Initializes bitboards in order to obtain the following board:
 * r n b q k b n r
 * p p p p p p p p
 * - - - - - - - -
 * - - - - - - - -
 * - - - - - - - -
 * - - - - - - - -
 * P P P P P P P P
 * R N B Q K B N R
 *
 * note that upper case letters represent white pieces while lower case letters are black pieces.
 */
Bitboard::Bitboard() {
	bitBoards[nBlack] = 0xffffL << 48;
	bitBoards[nWhite] = 0xffffL;
	bitBoards[nColor] = bitBoards[nWhite] | bitBoards[nBlack];

	bitBoards[nPawn] = (0xffL << 48) | (0xffL << 8);
	bitBoards[nKnight] = 0x42L | (0x42L << 56);
	bitBoards[nBishop] = 0x24L | (0x24L << 56);
	bitBoards[nRook] = 0x81L | (0x81L << 56);
	bitBoards[nQueen] = 0x8L | (0x8L << 56);
	bitBoards[nKing] = 0x10L | (0x10L << 56);
}


/**
 * @brief Constructor that uses a custom board, represented by the \p fen string.
 * @param fen  fen string that will be used to generate the bitboards
 */
Bitboard::Bitboard(std::string fen) {
	// Just to make sure that all bitboards start with value 0x0;
	for (auto& b : bitBoards)
		b.reset();

	int pos = 56;

	for (unsigned long int i = 0; i < fen.find_first_of(' '); i++) {
		switch (tolower(fen[i])) {
			case '/':			// do not increment counter because '/' does not represent any position
				pos -= 17;
				break;
			case 'p':
				bitBoards[nPawn].set(pos);
				if (fen[i] == 'P')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

			case 'n':
				bitBoards[nKnight].set(pos);
				if (fen[i] == 'N')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

			case 'b':
				bitBoards[nBishop].set(pos);
				if (fen[i] == 'B')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

			case 'r':
				bitBoards[nRook].set(pos);
				if (fen[i] == 'R')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

			case 'q':
				bitBoards[nQueen].set(pos);
				if (fen[i] == 'Q')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

			case 'k':
				bitBoards[nKing].set(pos);
				if (fen[i] == 'K')
					bitBoards[nWhite].set(pos);
				else
					bitBoards[nBlack].set(pos);
				break;

				// Is digit. Skip next n squares
			default:
				pos += fen[i] - '0' - 1; 			// -1 because it will be incremented at the end
				break;
		}

		pos++;

	}

	bitBoards[nColor] = bitBoards[nBlack] | bitBoards[nWhite];

}

/**
 * @details This method performs an AND operation between the bitboard containing all pawns and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getPawns(enumColor color) {
	return bitBoards[nPawn] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all knights and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getKnights(enumColor color) {
	return bitBoards[nKnight] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all bishops and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getBishops(enumColor color) {
	return bitBoards[nBishop] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all rooks and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getRooks(enumColor color) {
	return bitBoards[nRook] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all queens and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getQueens(enumColor color) {
	return bitBoards[nQueen] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all kings and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getKing(enumColor color) {
	return bitBoards[nKing] & bitBoards[color];
}

/**
 * @details This method returns a bitboard containing all pieces that match the parameter color .
 */
U64 Bitboard::getPieces(enumColor color) {
	return bitBoards[color];
}

/**
 * @details This method performs and AND operation between all white and black pieces, resulting in a bitboard that contains all the pieces on the board.
 */
U64 Bitboard::getAllPieces() {
	return bitBoards[nColor];
}

/**
 * @details Returns a pointer to the bitBoards attribute of the Bitboard class. Since this is a private attribute, it is treated as a constant to prevent modifications.
 */
U64 *Bitboard::getBitBoards() {
	return bitBoards;
}

/**
 * @details Converts the board from bitboards to a fancy string and prints it to stdout.
 */
void Bitboard::printBoard() {
	std::vector<std::string> board;

	std::string aux;
	long unsigned int i;

	for (i = 0; i < 64ul; i++)
		board.push_back("-");

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nPawn].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♟";
			else
				board[i] = "♙";
		}
	}

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nKnight].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♞";
			else
				board[i] = "♘";
		}
	}

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nBishop].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♝";
			else
				board[i] = "♗";
		}
	}

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nRook].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♜";
			else
				board[i] = "♖";
		}
	}

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nQueen].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♛";
			else
				board[i] = "♕";
		}
	}

	for (i = 0; i < 64ul; i++) {
		if (bitBoards[nKing].test(i)) {
			if (bitBoards[nWhite].test(i))
				board[i] = "♚";
			else
				board[i] = "♔";
		}
	}

	for (i = 0; i < 64; i += 8) {
		std::cout << "\033[1;33m" << (64 - i) / 8 << "  \033[0m";

		for (int j = int(i + 7); j >= int(i); j--)
			std::cout << board[63 - j] << " ";

		std::cout << std::endl;
	}

	std::cout << "   \033[1;33ma b c d e f g h\033[0m" << std::endl;
}


/**
 * @brief Performs a OR operation between the all white pieces and all black pieces. Result is stored on the nColor bitboard, which contains all pieces on the board.
 */
void Bitboard::updateBitboard() {
	bitBoards[nColor] = bitBoards[nWhite] | bitBoards[nBlack];
}

