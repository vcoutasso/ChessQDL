#include "tile.h"
#include "game.h"

using namespace xqdl;

Tile::Tile(bool white, int length, sf::Vector2f pos) {
	currentPiece = nullptr;
	shape = sf::RectangleShape(sf::Vector2f(length, length));
	shape.setFillColor(white ? xqdl::whiteTile : xqdl::blackTile);
	shape.setPosition(pos);
	length = 80;
}

void Tile::setPiece(Piece *piece) {
	currentPiece = piece;

	// Adjust image size to better fit board
	//currentPiece->sprite.setScale(sf::Vector2f(1.8, 1.8));
	currentPiece->sprite.setOrigin(sf::Vector2f(currentPiece->sprite.getLocalBounds().width / 2,
												currentPiece->sprite.getLocalBounds().height / 2));
	currentPiece->sprite.setPosition(shape.getPosition().x + shape.getSize().x / 2,
									 shape.getPosition().y + shape.getSize().y / 2);
}

bool Tile::isEmpty() {
	return currentPiece == nullptr;
}

bool Tile::isWhite() {
	return shape.getFillColor() == xqdl::whiteTile;
}
