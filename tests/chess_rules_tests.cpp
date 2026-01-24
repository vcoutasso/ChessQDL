#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Engine/engine.hpp"
#include "Engine/bitboard.hpp"
#include "Engine/movegen.hpp"

// Helper function to count set bits in a bitset
inline int popCount(chessqdl::U64 x) {
	return static_cast<int>(x.count());
}

// ============================================================================
// CASTLING TESTS
// ============================================================================

TEST(ChessRules, CastlingKingsideWhite_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, 0, board.getCastlingRights());
	
	// Check that e1g1 (kingside castling) is in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	EXPECT_TRUE(canCastleKingside);
}

TEST(ChessRules, CastlingQueensideWhite_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, 0, board.getCastlingRights());
	
	// Check that e1c1 (queenside castling) is in the move list
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_TRUE(canCastleQueenside);
}

TEST(ChessRules, CastlingKingsideBlack_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack, 0, board.getCastlingRights());
	
	// Check that e8g8 (kingside castling) is in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e8g8") != moves.end();
	EXPECT_TRUE(canCastleKingside);
}

TEST(ChessRules, CastlingQueensideBlack_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack, 0, board.getCastlingRights());
	
	// Check that e8c8 (queenside castling) is in the move list
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e8c8") != moves.end();
	EXPECT_TRUE(canCastleQueenside);
}

TEST(ChessRules, CastlingBlockedByPiece_Test) {
	// Knight on g1 blocks kingside castling
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K1NR w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, 0, board.getCastlingRights());
	
	// Check that e1g1 (kingside castling) is NOT in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	EXPECT_FALSE(canCastleKingside);
}

TEST(ChessRules, CastlingThroughCheck_Test) {
	// Bishop on a4 attacks d1 via diagonal a4-b3-c2-d1, castling queenside would move through check
	chessqdl::Bitboard board("4k3/8/8/8/b7/8/8/R3K2R w KQ - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, 0, board.getCastlingRights());
	
	// Check that e1c1 (queenside castling) is NOT in the move list (would pass through check on d1)
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_FALSE(canCastleQueenside);
}

TEST(ChessRules, CastlingWhileInCheck_Test) {
	// King is in check, cannot castle
	chessqdl::Bitboard board("4k3/8/8/8/8/4r3/8/R3K2R w KQ - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, 0, board.getCastlingRights());
	
	// Check that neither e1g1 nor e1c1 are in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_FALSE(canCastleKingside);
	EXPECT_FALSE(canCastleQueenside);
}

// ============================================================================
// PINNED PIECES TESTS
// ============================================================================

TEST(ChessRules, PinnedPieceCannotMove_Test) {
	// Bishop on e2 is pinned by rook on e8, cannot move
	chessqdl::Engine engine("4r3/8/8/8/8/8/4B3/4K3 w - - 0 1", chessqdl::nWhite, 1, false, true, 42);
	
	auto legalMoves = engine.getLegalMoves();
	
	// Bishop cannot move because it's pinned
	bool bishopCanMove = false;
	for (const auto& move : legalMoves) {
		if (move[0] == 'e' && move[1] == '2') {
			bishopCanMove = true;
			break;
		}
	}
	EXPECT_FALSE(bishopCanMove);
}

TEST(ChessRules, PinnedPieceCanCaptureAlongPin_Test) {
	// Rook on e4 is pinned by queen on e8, but can capture the queen along the pin
	// (A rook CAN move along the e-file, unlike a bishop which can only move diagonally)
	chessqdl::Engine engine("4q3/8/8/8/4R3/8/8/4K3 w - - 0 1", chessqdl::nWhite, 1, false, true, 42);
	
	auto legalMoves = engine.getLegalMoves();
	
	// Rook can capture the queen along the pin (e4e8 is a valid rook move)
	bool canCaptureQueen = std::find(legalMoves.begin(), legalMoves.end(), "e4e8") != legalMoves.end();
	EXPECT_TRUE(canCaptureQueen);
}

// ============================================================================
// SPECIAL PAWN MOVES TESTS
// ============================================================================

TEST(ChessRules, PawnCannotMoveBackward_Test) {
	chessqdl::Bitboard board("8/8/8/4P3/8/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Pawn should only be able to move forward to e6
	EXPECT_EQ(popCount(moves), 1);
}

TEST(ChessRules, PawnDoubleMoveFromInitialPosition_Test) {
	chessqdl::Bitboard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Each pawn can move 1 or 2 squares forward: 8 pawns * 2 moves = 16
	EXPECT_EQ(popCount(moves), 16);
}

TEST(ChessRules, PawnBlockedByPiece_Test) {
	// Pawn on e4 blocked by pawn on e5
	chessqdl::Bitboard board("8/8/8/4p3/4P3/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// White pawn cannot move
	EXPECT_EQ(moves, 0ULL);
}

TEST(ChessRules, PawnCanOnlyCaptureDiagonally_Test) {
	// Pawn can capture diagonally but not straight ahead if blocked
	chessqdl::Bitboard board("8/8/8/3ppp2/4P3/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPawnMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Should have 2 capture moves (e4d5 and e4f5)
	EXPECT_EQ(popCount(moves), 2);
}

// ============================================================================
// MOVE COUNTING AND PIECE MOVEMENT TESTS
// ============================================================================

TEST(ChessRules, InitialPositionHas20LegalMoves_Test) {
	chessqdl::Engine engine(chessqdl::nWhite, 1, false, true, 42);
	
	auto legalMoves = engine.getLegalMoves();
	
	// Starting position has exactly 20 legal moves for white
	EXPECT_EQ(legalMoves.size(), 20);
}

TEST(ChessRules, KnightMovesFromCorner_Test) {
	// Knight in corner has only 2 possible moves
	chessqdl::Bitboard board("8/8/8/8/8/8/8/N6K w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getKnightMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Knight on a1 can move to b3 and c2
	EXPECT_EQ(popCount(moves), 2);
}

TEST(ChessRules, KnightMovesFromCenter_Test) {
	// Knight in center has 8 possible moves
	chessqdl::Bitboard board("8/8/8/8/3N4/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getKnightMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Knight on d4 has 8 possible moves
	EXPECT_EQ(popCount(moves), 8);
}

TEST(ChessRules, KingCanMoveOneSquare_Test) {
	// King in center can move to 8 squares
	chessqdl::Bitboard board("8/8/8/8/3K4/8/8/8 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getKingMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// King on d4 has 8 possible moves
	EXPECT_EQ(popCount(moves), 8);
}

TEST(ChessRules, KingCannotMoveIntoCheck_Test) {
	// King cannot move into attack from rook
	chessqdl::Engine engine("8/8/8/8/8/4r3/8/3K4 w - - 0 1", chessqdl::nWhite, 1, false, true, 42);
	
	auto legalMoves = engine.getLegalMoves();
	
	// King cannot move to e1 (attacked by rook)
	bool canMoveToE1 = std::find(legalMoves.begin(), legalMoves.end(), "d1e1") != legalMoves.end();
	EXPECT_FALSE(canMoveToE1);
}

// ============================================================================
// BISHOP AND ROOK SLIDING MOVES TESTS
// ============================================================================

TEST(ChessRules, BishopDiagonalMoves_Test) {
	// Bishop on d4 with empty board
	chessqdl::Bitboard board("8/8/8/8/3B4/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getBishopMoves(board.getBitBoards(), chessqdl::nWhite, chessqdl::nBishop);
	
	// Bishop on d4 has 13 possible diagonal moves
	EXPECT_EQ(popCount(moves), 13);
}

TEST(ChessRules, RookOrthogonalMoves_Test) {
	// Rook on d4 with empty board
	chessqdl::Bitboard board("8/8/8/8/3R4/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getRookMoves(board.getBitBoards(), chessqdl::nWhite, chessqdl::nRook);
	
	// Rook on d4 has 14 possible orthogonal moves
	EXPECT_EQ(popCount(moves), 14);
}

TEST(ChessRules, QueenCombinedMoves_Test) {
	// Queen on d4 with empty board
	chessqdl::Bitboard board("8/8/8/8/3Q4/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getQueenMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Queen on d4 has 27 possible moves (bishop + rook moves)
	EXPECT_EQ(popCount(moves), 27);
}

TEST(ChessRules, SlidingPieceBlockedByOwnPiece_Test) {
	// Rook blocked by own pawn
	chessqdl::Bitboard board("8/8/8/8/3RP3/8/8/4K3 w - - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getRookMoves(board.getBitBoards(), chessqdl::nWhite, chessqdl::nRook);
	
	// Rook on d4 blocked by pawn on e4, should have 10 moves (not 14)
	EXPECT_LT(popCount(moves), 14);
}
