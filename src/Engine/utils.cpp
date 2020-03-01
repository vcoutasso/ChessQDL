#include "utils.hpp"
#include "movegen.hpp"

#include <cmath>
#include <iostream>

using namespace chessqdl;

/**
 * @details The method only takes into account the LSB of \p position. Thus, if there is more than 1 bit set (or even 0) the return value will not be accurate.
 */
std::string chessqdl::posToStr(uint64_t pos) {

	// Least significant set bit
	pos &= -pos;

	// log2(pos) is the index of the bit that is set
	return mapPositions[log2(pos)];
}


/**
 * @details Performs an evaluation that takes into account the material balance and number of available moves. <br>
 *
 * Piece value is as follows: <br>
 * King   - 200 <br>
 * Queen  - 9 <br>
 * Rook   - 5 <br>
 * Bishop - 3 <br>
 * Knight - 3 <br>
 * Pawn   - 1 <br>
 *
 * @todo Count only legal moves and create separate files for board evaluation
 */
int chessqdl::evaluateBoard(const BitbArray &board, enumColor color) {
	// King count
	int k = (board[nKing] & board[color]).count();
	int kPrime = board[nKing].count() - k;

	// Queen count
	int q = (board[nQueen] & board[color]).count();
	int qPrime = board[nQueen].count() - q;

	// Rook count
	int r = (board[nRook] & board[color]).count();
	int rPrime = board[nRook].count() - r;

	// Knight count
	int n = (board[nKnight] & board[color]).count();
	int nPrime = board[nKnight].count() - n;

	// Bishop count
	int b = (board[nBishop] & board[color]).count();
	int bPrime = board[nBishop].count() - b;

	// Pawn count
	int p = (board[nPawn] & board[color]).count();
	int pPrime = board[nPawn].count() - p;

	MoveGenerator gen;
	enumColor enemyColor = color == nWhite ? nBlack : nWhite;

	// Move count
	int m = gen.getPseudoLegalMoves(board, color).size();
	int mPrime = gen.getPseudoLegalMoves(board, enemyColor).size();

	int score = 200 * (k - kPrime) + 9 * (q - qPrime) + 5 * (r - rPrime) + 3 * (n - nPrime + b - bPrime) + (p - pPrime);
	score += 0.1 * (m - mPrime);

	//if (color == nBlack) score *= -1;

	return score;
}


/**
 * @details Ignore input if not a valid integer and keep reading from stdin until the input is valid
 */
void chessqdl::readInteger(int &n) {
	while (!(std::cin >> n)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


/**
 * @details Performs some bitset operations to encounter the least significant bit that is set. Log2 just finds out its index
 */
int chessqdl::leastSignificantSetBit(uint64_t value) {
	uint64_t lsb = value & -value;

	return log2(lsb);
}

/**
 * @details Receives two uint64_t, retrieves their position name in the board and constitutes the move that's being made
 */
std::string chessqdl::moveName(uint64_t from, uint64_t to) {
	std::string from_str = posToStr(from);
	std::string to_str = posToStr(to);

	return from_str.append(to_str);
}
