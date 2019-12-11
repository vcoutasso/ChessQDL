#ifndef CHESSQDL_UTILS_H
#define CHESSQDL_UTILS_H

#include "const.h"

namespace chessqdl {

	/**
	 * @brief This methods returns the equivalent position of the set bit to the board. For example 0x01 would return a1, 0x02 a2 and so on.
	 * @param position  bitboard containing one
	 * @return Name of the square that represents the least significant bit of \p position
	 */
	std::string posToStr(uint64_t pos);
}

#endif //CHESSQDL_UTILS_H
