#ifndef CHESSQDL_UTILS_HPP
#define CHESSQDL_UTILS_HPP

#include "const.hpp"

namespace chessqdl {

	/**
	 * @brief This methods returns the equivalent position of the set bit to the board. For example 0x01 would return a1, 0x02 a2 and so on.
	 * @param position  bitboard (preferably with only one bit set)
	 * @return Name of the square that represents the least significant bit of \p position
	 */
	std::string posToStr(uint64_t pos);


	/**
	 * @brief Heuristic function to evaluate the color.
	 * @param board  board to evaluate
	 * @param color  here colors defines the perspective of the evaluation. If the board is better for the \p color pieces, result will be positive. Otherwise, it will be negative
	 * @return Score of the board indicating who has the advantage
	 */
	int evaluateBoard(const BitbArray &board, enumColor color);


	/**
	 * @brief Method to read a integer from stdin in a clean and sanitized way.
	 * @param n  variable that will store the integer read from std::cin
	 */
	void readInteger(int &n);

	/**
	 * @brief Method to return the index of the least significant bit of \p value that is set
	 * @param value  number of interest
	 * @return Index of least significant bit that is set
	 */
	int leastSignificantSetBit(uint64_t value);

	/**
	 * @brief Constructs the name of the move that is formed by moving from \p from to \p to
	 * @param from  unsigned long int with only one bit set signifying the original position of the moving piece
	 * @param to  unsigned long int with only one bit set signifying the destination position of the moving piece
	 * @return Name of the move that is being made (e.g e2e4)
	 */
	std::string moveName(uint64_t from, uint64_t to);

	typedef struct scoreStruct scoreStruct;

	struct scoreStruct {
		int score;
		std::string move;
	};


}

#endif //CHESSQDL_UTILS_HPP
