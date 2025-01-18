#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(const int argc, char **argv) {

	// Arguments
	int level;
	enumColor enginePieces;
	bool verbose;
	bool pvp;
	std::string fen;

	// Parse arguments and initialize variables
	argumentParser(argc, argv, level, enginePieces, verbose, fen, pvp);

	// Construct engine
	Engine engine(enginePieces, level, verbose, pvp);

	if (!fen.empty())
		engine = Engine(fen, enginePieces, level, verbose, pvp);

	// Call engine's parser to start interaction
	engine.parser();

	return 0;
}