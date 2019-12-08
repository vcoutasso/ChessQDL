#include "src/GUI/game.h"
#include "src/Engine/engine.h"

using namespace chessqdl;

int main() {

	/*Game game;
	game.mainMenu();*/

	Engine engine("r1bqk1nr/pppp1ppp/2n5/2b1p3/1PB1P3/5N2/P1PP1PPP/RNBQK2R b KQkq b3 1 4");

	engine.start();

	return 0;
}