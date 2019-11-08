#include "bitboard.h"
#include <string.h>

using namespace chessqdl;

Bitboard::Bitboard() {

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




