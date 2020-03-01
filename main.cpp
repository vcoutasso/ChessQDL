#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(int argc, char **argv) {

	// Arguments
	int level;
	enumColor enginePieces;
	bool verbose;

	// Parse arguments and initialize variables
	argumentParser(argc, argv, level, enginePieces, verbose);

	// Construct engine
	Engine engine(enginePieces, level, verbose);

	// Call engine's parser to start interaction
	engine.parser();

	return 0;
}