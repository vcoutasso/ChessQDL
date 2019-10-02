#ifndef CHESSQDL_PIECE_H
#define CHESSQDL_PIECE_H

#include <SFML/Graphics.hpp>

namespace xqdl {

	enum class enumColor {
		White,
		Black
	};

	class Piece {
	protected:
		sf::Texture texture;

	public:
		virtual int move() = 0;

		bool hasMoved;

		Piece();
		void loadTexture(const std::string &path);

		sf::Sprite sprite;
	};


	class Pawn : public Piece {
	public:
		Pawn(bool white);

		int move();

	};

	class Knight : public Piece {
	public:
		Knight(bool white);

		int move();

	};

	class Bishop : public Piece {
	public:
		Bishop(bool white);

		int move();

	};

	class Rook : public Piece {
	public:
		Rook(bool white);

		int move();

	};

	class Queen : public Piece {
	public:
		Queen(bool white);

		int move();

	};

	class King : public Piece {
	public:
		King(bool white);

		int move();

	};

}
#endif //CHESSQDL_PIECE_H
