#include "bitboard.h"

#include <string>
#include <iostream>
#include <algorithm>

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
 * note that upper case letters represent white pieces while lower case leters are black pieces.
 */
Bitboard::Bitboard() {
	bitBoards[pieceColor::nBlack] = 0xffffL << 48;
	bitBoards[pieceColor::nWhite] = 0xffffL;

	bitBoards[pieceType::nPawn] = (0xffL << 48) + (0xffL << 8);
	bitBoards[pieceType::nKnight] = 0x42L + (0x42L << 56);
	bitBoards[pieceType::nBishop] = 0x24L + (0x24L << 56);
	bitBoards[pieceType::nRook] = 0x81L + (0x81L << 56);
	bitBoards[pieceType::nQueen] = 0x8L + (0x8L << 56);
	bitBoards[pieceType::nKing] = 0x10L + (0x10L << 56);
}

/**
 * @details This method performs an AND operation between the bitboard containing all pawns and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getPawns(Bitboard::pieceColor color) {
	return bitBoards[nPawn] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all knights and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getKnights(Bitboard::pieceColor color){
	return bitBoards[nKnight] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all bishops and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getBishops(Bitboard::pieceColor color){
	return bitBoards[nBishop] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all rooks and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getRooks(Bitboard::pieceColor color) {
	return bitBoards[nRook] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all queens and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getQueens(Bitboard::pieceColor color){
	return bitBoards[nQueen] & bitBoards[color];
}

/**
 * @details This method performs an AND operation between the bitboard containing all kings and the bitboard containing all pieces of the desired color
 */
U64 Bitboard::getKing(Bitboard::pieceColor color){
	return bitBoards[nKing] & bitBoards[color];
}

/**
 * @details This method returns a bitboard containing all pieces that match the parameter color .
 */
U64 Bitboard::getPieces(Bitboard::pieceColor color) {
	return bitBoards[color];
}

/**
 * @details This method performs and AND operation between all white and black pieces, resulting in a bitboard that contains all the pieces on the board.
 */
U64 Bitboard::getAllPieces() {
	return bitBoards[pieceColor::nBlack] & bitBoards[pieceColor::nWhite];
}

/**
 * @details Converts the board from bitboards to a readable string and prints it to stdout. It does so very inefficiently, but since its main purpose is to help debugging, it shouldn't be a big deal for now.
 */
void Bitboard::printBoard() {
	std::string board(64, '-');
	std::string aux;

	aux = bitBoards[pieceType::nPawn].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'p';
	}

	aux = bitBoards[pieceType::nKnight].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'n';
	}

	aux = bitBoards[pieceType::nBishop].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'b';
	}

	aux = bitBoards[pieceType::nRook].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'r';
	}

	aux = bitBoards[pieceType::nQueen].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'q';
	}

	aux = bitBoards[pieceType::nKing].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = 'k';
	}

	aux = bitBoards[pieceColor::nBlack].to_string();
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i] == '1')
			board[i] = board[i] - 32;
	}

	std::reverse(board.begin(), board.end());
	for (int i = 0; i < board.size(); i++) {
		if (!(i % 8))
			std::cout << std::endl;
		std::cout << board[i];
	}
}
