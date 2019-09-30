#ifndef CHESSQDL_GAME_H
#define CHESSQDL_GAME_H

#include <SFML/Graphics.hpp>

namespace xqdl {

	const sf::Color whiteTile = sf::Color(255, 206, 158);
	const sf::Color blackTile = sf::Color(209, 139, 71);

	class Game {
	private:
		sf::RenderWindow window;

		void createWindow();

		int startGame();

		void drawBoard();

	public:
		Game();

		void mainMenu();
	};
}

#endif //CHESSQDL_GAME_H
