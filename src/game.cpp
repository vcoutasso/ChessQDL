#include "game.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace xqdl;

Game::Game() {
	createWindow();

	sf::Vector2u wsize = window.getSize();
	bool isWhite = true;
	int length = 80;
	int offsetX = ((int) wsize.x - 8 * length) / 2;
	int offsetY = ((int) wsize.y - 8 * length) / 2;

	// TODO: Fix tiles order! tiles[0] should be a1 (i think)

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			tiles[row * 8 + col] = Tile(isWhite, length, sf::Vector2f(offsetX + col * length, offsetY + row * length));
			isWhite = !isWhite;
		}
		isWhite = !isWhite;
	}

	// TODO: Delete this and make something decent.

	tiles[0].setPiece(new Rook(false));
	tiles[1].setPiece(new Knight(false));
	tiles[2].setPiece(new Bishop(false));
	tiles[3].setPiece(new Queen(false));
	tiles[4].setPiece(new King(false));
	tiles[5].setPiece(new Bishop(false));
	tiles[6].setPiece(new Knight(false));
	tiles[7].setPiece(new Rook(false));
	tiles[8].setPiece(new Pawn(false));
	tiles[9].setPiece(new Pawn(false));
	tiles[10].setPiece(new Pawn(false));
	tiles[11].setPiece(new Pawn(false));
	tiles[12].setPiece(new Pawn(false));
	tiles[13].setPiece(new Pawn(false));
	tiles[14].setPiece(new Pawn(false));
	tiles[15].setPiece(new Pawn(false));

	tiles[48].setPiece(new Pawn(true));
	tiles[49].setPiece(new Pawn(true));
	tiles[50].setPiece(new Pawn(true));
	tiles[51].setPiece(new Pawn(true));
	tiles[52].setPiece(new Pawn(true));
	tiles[53].setPiece(new Pawn(true));
	tiles[54].setPiece(new Pawn(true));
	tiles[55].setPiece(new Pawn(true));
	tiles[56].setPiece(new Rook(true));
	tiles[57].setPiece(new Knight(true));
	tiles[58].setPiece(new Bishop(true));
	tiles[59].setPiece(new Queen(true));
	tiles[60].setPiece(new King(true));
	tiles[61].setPiece(new Bishop(true));
	tiles[62].setPiece(new Knight(true));
	tiles[63].setPiece(new Rook(true));

	mainMenu();
}

void Game::createWindow() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(1024, 768), "ChessQDL", sf::Style::Default, settings);
}

void Game::mainMenu() {

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (startGame() == -1)
				window.close();
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
	}
}

int Game::startGame() {


	while (window.isOpen()) {
		sf::Event event{};

		while (window.pollEvent(event)) {

			drawBoard();

			if (event.type == sf::Event::Closed)
				return -1;

		}
		window.display();
	}

	return 0;
}

void Game::drawBoard() {

	window.clear(sf::Color::White);

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			window.draw(tiles[row * 8 + col].shape);
		}
	}

	drawPieces();
}

void Game::drawPieces() {

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			if (tiles[row * 8 + col].currentPiece != nullptr)
				window.draw(tiles[row * 8 + col].currentPiece->sprite);
		}
	}

	window.display();
}