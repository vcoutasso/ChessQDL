#include "piece.h"
#include <iostream>

using namespace xqdl;

// TODO: Fix pieces resolution
void Piece::loadTexture(const std::string &path) {
	if (!texture.loadFromFile(path))
		std::cout << "Error: Could not load texture! Path to file: " << path << std::endl;
	else {
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}
}

Pawn::Pawn(bool white) {
	if (white == 1)
		loadTexture("img/wPawn.png");
	else
		loadTexture("img/bPawn.png");
}

int Pawn::move() {
	return 1;
}

Knight::Knight(bool white) {
	if (white == 1)
		loadTexture("img/wKnight.png");
	else
		loadTexture("img/bKnight.png");
}

int Knight::move() {

}

Bishop::Bishop(bool white) {
	if (white == 1)
		loadTexture("img/wBishop.png");
	else
		loadTexture("img/bBishop.png");
}

int Bishop::move() {

}

Rook::Rook(bool white) {
	if (white == 1)
		loadTexture("img/wRook.png");
	else
		loadTexture("img/bRook.png");
}

int Rook::move() {

}

Queen::Queen(bool white) {
	if (white == 1)
		loadTexture("img/wQueen.png");
	else
		loadTexture("img/bQueen.png");
}

int Queen::move() {

}


King::King(bool white) {
	if (white == 1)
		loadTexture("img/wKing.png");
	else
		loadTexture("img/bKing.png");
}

int King::move() {

}
