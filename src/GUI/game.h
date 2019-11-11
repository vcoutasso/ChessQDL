#ifndef CHESSQDL_GAME_H
#define CHESSQDL_GAME_H

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "board.h"

namespace chessqdl {

	const auto whiteTile = sf::Color(255, 206, 158);
	const auto blackTile = sf::Color(209, 139, 71);

	class Game {
	private:
		sf::RenderWindow window;
		Tile tiles[64];
		Board board;

		sf::Font font;

		void createWindow();

		void initTiles();

		int startGame();

		void drawBoard();

		void drawPieces();

		void movePiece(sf::Event&);


	public:
		Game();

		void mainMenu();
	};
}

#endif //CHESSQDL_GAME_H
