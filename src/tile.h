#ifndef CHESSQDL_TILE_H
#define CHESSQDL_TILE_H

#include <SFML/Graphics.hpp>
#include "piece.h"

namespace chessqdl {

	const auto tileSize = 80;

	class Tile {
	private:


	public:
		Piece *currentPiece;
		sf::RectangleShape shape;

		Tile(bool white, int length, sf::Vector2f pos);

		Tile() = default;

		bool isWhite();

		bool isEmpty();

		void setPiece(Piece *piece);

	};
}


#endif //CHESSQDL_TILE_H
