#ifndef CHESSQDL_MOVEGEN_H
#define CHESSQDL_MOVEGEN_H

#include "bitboard.h"

namespace chessqdl {

	class MoveGenerator {

	public:
		MoveGenerator() = default;

		U64 shiftNorth(U64 bitboard);

		U64 shiftNorthEast(U64 bitboard);

		U64 shiftEast(U64 bitboard);

		U64 shiftSouthEast(U64 bitboard);

		U64 shiftSouth(U64 bitboard);

		U64 shiftSouthWest(U64 bitboard);

		U64 shiftWest(U64 bitboard);

		U64 shiftNorthWest(U64 bitboard);



	};

}


#endif //CHESSQDL_MOVEGEN_H
