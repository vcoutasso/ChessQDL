#include "game.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace xqdl;

Game::Game() {
	createWindow();
	mainMenu();
}

void Game::createWindow() {
	window.create(sf::VideoMode(1024, 768), "ChessQDL");
}

void Game::mainMenu() {

	while (window.isOpen()) {
		sf::Event event;
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
		sf::Event event;

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
	sf::Vector2u wsize = window.getSize();

	bool isWhite = true;
	int length = 80;
	int offsetX = (wsize.x - 8 * length) / 2;
	int offsetY = (wsize.y - 8 * length) / 2;

	window.clear(sf::Color::White);

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			sf::RectangleShape tile(sf::Vector2f(length, length));
			tile.setFillColor(isWhite ? xqdl::whiteTile : xqdl::blackTile);
			tile.setPosition(offsetX + col * length, offsetY + row * length);
			window.draw(tile);
			isWhite = !isWhite;
		}
		isWhite = !isWhite;
	}

	window.display();
}