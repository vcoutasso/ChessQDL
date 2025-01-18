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
	return mapPositions[leastSignificantSetBit(pos)];
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
int chessqdl::evaluateBoard(const BitboardArray &board, const enumColor color) {
	// King count
	const int k = static_cast<int>((board[nKing] & board[color]).count());
	const int kPrime = static_cast<int>(board[nKing].count() - k);

	// Queen count
	const int q = static_cast<int>((board[nQueen] & board[color]).count());
	const int qPrime = static_cast<int>(board[nQueen].count() - q);

	// Rook count
	const int r = static_cast<int>((board[nRook] & board[color]).count());
	const int rPrime = static_cast<int>(board[nRook].count() - r);

	// Knight count
	const int n = static_cast<int>((board[nKnight] & board[color]).count());
	const int nPrime = static_cast<int>(board[nKnight].count() - n);

	// Bishop count
	const int b = static_cast<int>((board[nBishop] & board[color]).count());
	const int bPrime = static_cast<int>(board[nBishop].count() - b);

	// Pawn count
	const int p = static_cast<int>((board[nPawn] & board[color]).count());
	const int pPrime = static_cast<int>(board[nPawn].count() - p);

	const enumColor enemyColor = color == nWhite ? nBlack : nWhite;

	// Move count
	const int m = static_cast<int>(MoveGenerator::getPseudoLegalMoves(board, color).size());
	const int mPrime = static_cast<int>(MoveGenerator::getPseudoLegalMoves(board, enemyColor).size());

	int score = 200 * (k - kPrime) + 9 * (q - qPrime) + 5 * (r - rPrime) + 3 * (n - nPrime + b - bPrime) + (p - pPrime);
	score += static_cast<int>(0.1 * (m - mPrime));

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
int chessqdl::leastSignificantSetBit(const uint64_t value) {
	const uint64_t lsb = value & -value;

	return static_cast<int>(log2(static_cast<double>(lsb)));
}


/**
 * @details Receives two uint64_t, retrieves their position name in the board and constitutes the move that's being made
 */
std::string chessqdl::moveName(const uint64_t from, const uint64_t to) {
	std::string from_str = posToStr(from);
	const std::string to_str = posToStr(to);

	return from_str.append(to_str);
}
