#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(int argc, char **argv) {

	int level;
	enumColor enginePieces;
	argumentParser(argc, argv, level, enginePieces);

	Engine engine(enginePieces, level);

	engine.parser();

	return 0;
}