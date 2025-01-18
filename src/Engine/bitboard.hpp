#ifndef CHESSQDL_BITBOARD_HPP
#define CHESSQDL_BITBOARD_HPP

#include <bitset>

#include "const.hpp"

namespace chessqdl {

	class Bitboard {

	private:

		/**
		 * @brief Array containing all bitboards. Indexing follows numColor and enumPiece
		 */
		BitboardArray bitBoards;

	public:

		/**
		 * @brief Default constructor. Initializes bitBoards according to a default initial chess board.
		 */
		Bitboard();

		/**
		 * @brief FEN constructor. Initializes bitBoards according to the given FEN string.
 	     * @param fen  fen string that will be used to generate the bitboards
		 */
		explicit Bitboard(const std::string &fen);

		/**
		 * @brief Returns a bitboard containing all pawns of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all pawns of a given color piece
		 */
		U64 getPawns(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all knights of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all knights of a given piece color
		 */
		U64 getKnights(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all bishops of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all bishops of a given piece color
		 */
		U64 getBishops(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all rooks of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all rooks of a given piece color
		 */
		U64 getRooks(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all queens of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all queens of a given piece color
		 */
		U64 getQueens(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing the king of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing the king of a given piece color
		 */
		U64 getKing(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all pieces of a given color
		 * @param color  the color of desired pieces (nWhite or nBlack)
		 * @return a bitboard containing all pieces of a given piece color
		 */
		U64 getPieces(enumColor color) const;


		/**
		 * @brief Returns a bitboard containing all pieces of a given type
		 * @param type  the type of desired pieces (e.g. nPawn)
		 * @return a bitboard containing all pieces of a given piece type
		 */
		U64 getPieces(enumPiece type) const;


		/**
		 * @brief Returns a bitboard containing all pieces at index \p i
		 * @param i  the desired index
		 * @return a bitboard containing all pieces at index \p i
		 */
		U64 getPiecesAt(int i) const;


		/**
		 * @brief Returns a bitboard containing all board pieces
		 * @return a bitboard containing all board pieces
		 */
		U64 getAllPieces() const;


		/**
		 * @brief Resets a specific bit on the bitboard that matches \p color
		 * @param color color of the target bitboard
		 * @param idx  number of the bit to reset
		 */
		void resetBit(enumColor color, int idx);


		/**
		 * @brief Resets a specific bit on the bitboard that matches \p piece
		 * @param piece  piece type of the target bitboard
		 * @param idx  number of the bit to reset
		 */
		void resetBit(enumPiece piece, int idx);


		/**
		 * @brief Resets a specific bit on the bitboard of index \i
		 * @param i  index of the bitboard
		 * @param idx  number of the bit to reset
		 */
		void resetBit(int i, int idx);


		/**
		 * @brief Sets a specific bit on the bitboard that matches \p color
		 * @param color color of the target bitboard
		 * @param idx  number of the bit to set
		 */
		void setBit(enumColor color, int idx);


		/**
		 * @brief Sets a specific bit on the bitboard that matches \p piece
		 * @param piece  piece type of the target bitboard
		 * @param idx  number of the bit to set
		 */
		void setBit(enumPiece piece, int idx);


		/**
		 * @brief Sets a specific bit on the bitboard of index \i
		 * @param i  index of the bitboard
		 * @param idx  number of the bit to set
		 */
		void setBit(int i, int idx);


		/**
		 * @brief Tests a specific bit on the bitboard that matches \p color
		 * @param color color of the target bitboard
		 * @param idx  number of the bit to test
		 * @return true if the bit is set, false otherwise
		 */
		bool testBit(enumColor color, int idx) const;


		/**
		 * @brief Tests a specific bit on the bitboard that matches \p piece
		 * @param piece  piece type of the target bitboard
		 * @param idx  number of the bit to test
		 * @return true if the bit is set, false otherwise
		 */
		bool testBit(enumPiece piece, int idx) const;


		/**
		 * @brief Tests a specific bit on the bitboard of index \i
		 * @param i  index of the bitboard
		 * @param idx  number of the bit to test
		 * @return true if the bit is set, false otherwise
		 */
		bool testBit(int i, int idx) const;


		/**
		 * @brief Returns the bitBoard attribute of the class
		 * @return an array containing all bitboards
		 */
		BitboardArray getBitBoards() const;


		/**
		 * @brief Prints current state of the board to stdout. Mainly for debugging purposes.
		 */
		void printBoard() const;


		/**
		 * @brief Updates the nColor bitboard
		 */
		void updateBitboard();

	};

}

#endif //CHESSQDL_BITBOARD_HPP
