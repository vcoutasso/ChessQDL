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

		/**
		 * @brief En passant square, if any. 0 if no en passant is available
		 */
		int enPassantSquare = 0;

		/**
		 * @brief Castling rights flags
		 * Each bit represents a castling right:
		 * bit 0: White kingside (K)
		 * bit 1: White queenside (Q)
		 * bit 2: Black kingside (k)
		 * bit 3: Black queenside (q)
		 */
		int castlingRights = 0b1111;

		/**
		 * @brief Halfmove clock for 50-move rule
		 * Incremented after each move, reset after pawn move or capture
		 */
		int halfmoveClock = 0;

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
		 * @brief Returns the en passant square
		 * @return the en passant square, or 0 if no en passant is available
		 */
		int getEnPassantSquare() const;

		
		/**
		 * @brief Sets the en passant square for the current position
		 * @param square the en passant target square (0 to clear en passant)
		 */
		void setEnPassantSquare(int square);


		/**
		 * @brief Returns the castling rights as a bitfield
		 * @return castling rights (bits: 0=K, 1=Q, 2=k, 3=q)
		 */
		int getCastlingRights() const;


		/**
		 * @brief Sets the castling rights
		 * @param rights castling rights as a bitfield (bits: 0=K, 1=Q, 2=k, 3=q)
		 */
		void setCastlingRights(int rights);


		/**
		 * @brief Checks if a specific castling right is available
		 * @param color the color (nWhite or nBlack)
		 * @param kingSide true for kingside castling, false for queenside
		 * @return true if the castling right is available
		 */
		bool canCastle(enumColor color, bool kingSide) const;


		/**
		 * @brief Removes a specific castling right
		 * @param color the color (nWhite or nBlack)
		 * @param kingSide true for kingside castling, false for queenside
		 */
		void removeCastlingRight(enumColor color, bool kingSide);


		/**
		 * @brief Returns castling rights as a FEN string (e.g., "KQkq", "Kq", "-")
		 * @return castling rights FEN string
		 */
		std::string getCastlingFEN() const;


		/**
		 * @brief Returns the halfmove clock (for 50-move rule)
		 * @return halfmove clock value
		 */
		int getHalfmoveClock() const;


		/**
		 * @brief Sets the halfmove clock
		 * @param clock the halfmove clock value
		 */
		void setHalfmoveClock(int clock);


		/**
		 * @brief Increments the halfmove clock by 1
		 */
		void incrementHalfmoveClock();


		/**
		 * @brief Resets the halfmove clock to 0 (called after pawn move or capture)
		 */
		void resetHalfmoveClock();


		/**
		 * @brief Generates the piece placement portion of a FEN string from the current board state.
		 * Format: rank 8 to rank 1, with files a-h. Empty squares are digits (1-8), pieces are letters.
		 * @return piece placement portion of FEN (e.g., "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR")
		 */
		std::string getPiecePlacementFEN() const;


		/**
		 * @brief Prints the current board state to stdout
		 */
		void printBoard() const;


		/**
		 * @brief Updates the nColor bitboard
		 */
		void updateBitboard();

	};

}

#endif //CHESSQDL_BITBOARD_HPP
