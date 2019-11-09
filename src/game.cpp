#include "game.h"
#include "board.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace chessqdl;

Game::Game() {
	createWindow();
	font.loadFromFile("resources/fonts/arial.ttf");

	mainMenu();
}

//
void Game::initTiles() {
	sf::Vector2u wsize = window.getSize();
	bool isWhite = true;
	int offsetX = ((int) wsize.x - 8 * chessqdl::tileSize) / 2;
	int offsetY = ((int) wsize.y - 8 * chessqdl::tileSize) / 2;


	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			tiles[row * 8 + col] = Tile(isWhite, chessqdl::tileSize, sf::Vector2f(offsetX + col * chessqdl::tileSize, offsetY + (7 - row) * chessqdl::tileSize));
			isWhite = !isWhite;
		}
		isWhite = !isWhite;
	}

	std::string pieces = board.FEN.substr(0, board.FEN.find_first_of(' '));

	int aux = 0;

	for (int i = 0; i < pieces.length(); ++i) {
		char ch = pieces.at(i);

		if (ch == '/')
			continue;

		else if (ch >= '1' and ch <= '9') {
			aux += ch - '0';
			continue;
		}

			// Define piece color
		else isWhite = !(ch < 'a' || ch > 'z');

		if (ch == 'p' || ch == 'P')
			tiles[aux].setPiece(new Pawn(isWhite));
		else if (ch == 'n' || ch == 'N')
			tiles[aux].setPiece(new Knight(isWhite));
		else if (ch == 'b' || ch == 'B')
			tiles[aux].setPiece(new Bishop(isWhite));
		else if (ch == 'r' || ch == 'R')
			tiles[aux].setPiece(new Rook(isWhite));
		else if (ch == 'q' || ch == 'Q')
			tiles[aux].setPiece(new Queen(isWhite));
		else if (ch == 'k' || ch == 'K')
			tiles[aux].setPiece(new King(isWhite));

		++aux;
	}

}

void Game::createWindow() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	window.create(sf::VideoMode(1024, 768), "ChessQDL", sf::Style::Default, settings);
	window.setFramerateLimit(24);
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

	initTiles();


	while (window.isOpen()) {
		sf::Event event{};

		drawBoard();
		while (window.pollEvent(event)) {
			switch (event.type) {
				case (sf::Event::Closed):
					return -1;

				case (sf::Event::MouseButtonPressed):
					if (event.mouseButton.button == sf::Mouse::Button::Left) {
						movePiece(event);
					}
					break;

				default:
					break;
			}

		}
		window.display();
	}

	return 0;
}

void Game::drawBoard() {
	sf::Text text;
	text.setFont(font);
	text.setString("a");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);

	char ch = 'A';
	char num = '1';

	// Always the same
	sf::Vector2f size = tiles[0].shape.getSize();

	window.clear(sf::Color::White);

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			window.draw(tiles[row * 8 + col].shape);

			// Labels a - h
			if (row == 0) {
				// First row
				sf::Vector2f pos = tiles[row * 8 + col].shape.getPosition();
				text.setString(ch);
				text.setOrigin(0, 0);
				text.setPosition(pos.x + size.x / 2 - text.getLocalBounds().width / 2, pos.y + size.y);
				window.draw(text);

				// Last row
				pos = tiles[7 * 8 + col].shape.getPosition();
				// This 5 just shifts labels upwards so the g doesn't overlap with the tiles. Actually an arbitrary value. Bad practice but might fix it later idk
				text.setPosition(pos.x + size.x / 2 - text.getLocalBounds().width / 2,
								 pos.y - text.getCharacterSize() - 5);
				window.draw(text);

				++ch;
			}

			// Labels 1 - 8
			if (col ==  0) {
				// First col
				sf::Vector2f pos = tiles[row * 8 + col].shape.getPosition();
				text.setString(num);
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(pos.x - text.getCharacterSize() / 2, pos.y + size.y / 2 - text.getLocalBounds().height / 2);
				window.draw(text);

				// Last col
				pos = tiles[row * 8 + 7].shape.getPosition();
				text.setPosition(pos.x + size.x + text.getCharacterSize() / 2, pos.y + size.y / 2 - text.getLocalBounds().height / 2);
				window.draw(text);

				++num;
			}
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


void Game::movePiece(sf::Event &event) {
	int src, dest;

	for (src = 0; src < 64; src++) {
		if (tiles[src].shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			break;
		}
	}

	if (tiles[src].currentPiece != nullptr) {

		// Wait for next sf::Event::MouseButtonPressed event to indicate where the piece will be moved to.
		while (window.waitEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					break;
		}

		for (dest = 0; dest < 64; dest++) {
			if (tiles[dest].shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				break;
		}

		// Animation
		sf::Vector2f currentPos = tiles[src].currentPiece->sprite.getPosition();
		sf::Vector2f newPos = sf::Vector2f(tiles[dest].shape.getPosition().x + tiles[dest].shape.getSize().x / 2, tiles[dest].shape.getPosition().y + tiles[dest].shape.getSize().y / 2);
		sf::Vector2f p = newPos - currentPos;

		for (int i = 0; i < 4; i++) {
			tiles[src].currentPiece->sprite.move(sf::Vector2f(p.x/5, p.y/5));
			drawBoard();
		}

		tiles[dest].setPiece(tiles[src].currentPiece);
		tiles[src].currentPiece = nullptr;

		drawBoard();
	}
	else
		std::cout << "No piece to move!" << std::endl; std::cout.flush();
}
