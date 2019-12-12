#ifndef CHESSQDL_UTILS_H
#define CHESSQDL_UTILS_H

#include "const.h"

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
	int evaluateBoard(const U64 *board, enumColor color);

	typedef struct scoreStruct scoreStruct;

	struct scoreStruct {
		int score;
		std::string move;
	};

}

#endif //CHESSQDL_UTILS_H
