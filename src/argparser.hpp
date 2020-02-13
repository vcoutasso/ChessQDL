#ifndef CHESSQDL_ARGPARSER_HPP
#define CHESSQDL_ARGPARSER_HPP

#include <iostream>
#include <cxxopts.hpp>
#include "Engine/utils.hpp"

using namespace chessqdl;


void argumentParser(int argc, char **argv, int &level, enumColor &enginePieces) {
	cxxopts::Options options("ChessQDL", "Simple chess engine with a terminal interface");

	options.add_options()
			("play_as_black", "Play with black pieces against the engine's white pieces")
			("l,level", "Level of the engine. The higher the value, the higher the difficulty. Accepted values range from 1 to 10", cxxopts::value(level))
			("h,help", "Display this help and exit");

	try {
		auto args = options.parse(argc, argv);

		if (args.count("help")) {
			std::cout << options.help();
			exit(0);
		}
		if (args.count("level")) {
			if (args["level"].as<int>() > 10 || args["level"].as<int>() < 1) {
				std::cout << "ChessQDL: Argument value is not valid" << std::endl;
				exit(1);
			} else level = args["level"].as<int>();
		} else level = 3;

		if (args.count("play_as_black"))
			enginePieces = nWhite;
		else
			enginePieces = nBlack;
	} catch (cxxopts::OptionException &e) {
		std::cout << "ChesssQDL: " << e.what() << std::endl;
		exit(1);
	}
}

#endif //CHESSQDL_ARGPARSER_HPP
