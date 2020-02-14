#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(int argc, char **argv) {

	int level;
	enumColor enginePieces;
	bool verbose;

	argumentParser(argc, argv, level, enginePieces, verbose);

	Engine engine(enginePieces, level, verbose);

	engine.parser();

	return 0;
}