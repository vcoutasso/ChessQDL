#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(int argc, char **argv) {

	// Arguments
	int level;
	enumColor enginePieces;
	bool verbose;
	std::string fen;

	// Parse arguments and initialize variables
	argumentParser(argc, argv, level, enginePieces, verbose, fen);

	// Construct engine
	Engine engine(enginePieces, level, verbose);

	if (!fen.empty())
		engine = Engine(fen, enginePieces, level, verbose);

	// Call engine's parser to start interaction
	engine.parser();

	return 0;
}