#include "ChessQDL/chessqdl.hpp"

using namespace chessqdl;

int main(const int argc, char **argv) {

	// Arguments
	int level;
	enumColor enginePieces;
	bool verbose;
	bool pvp;
	std::string fen;
	std::optional<int> seed;

	// Parse arguments and initialize variables
	argumentParser(argc, argv, level, enginePieces, verbose, fen, pvp, seed);

	// Construct engine
	Engine engine = fen.empty()
		                ? Engine(enginePieces, level, verbose, pvp, seed)
		                : Engine(fen, enginePieces, level, verbose, pvp, seed);

	// Call engine's parser to start interaction
	engine.parser();

	return 0;
}