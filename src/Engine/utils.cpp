#include "utils.h"

#include <cmath>

using namespace chessqdl;

/**
 * @details The method only takes into account the LSB of \p position. Thus, if there is more than 1 bit set (or even 0) the return value will not be accurate.
 * Therefore, if NDEBUG is not set and \p position has more than 1 bit set (or 0), the assert statement will evaluate to false and the program execution will terminate
 */
std::string chessqdl::posToStr(uint64_t pos) {

	// Least significant set bit
	pos &= -pos;

	// log2(pos) is the index of the bit that is set
	return mapPositions[log2(pos)];
}

