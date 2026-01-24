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
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Check that e1g1 (kingside castling) is in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	EXPECT_TRUE(canCastleKingside);
}

TEST(ChessRules, CastlingQueensideWhite_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Check that e1c1 (queenside castling) is in the move list
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_TRUE(canCastleQueenside);
}

TEST(ChessRules, CastlingKingsideBlack_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack);
	
	// Check that e8g8 (kingside castling) is in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e8g8") != moves.end();
	EXPECT_TRUE(canCastleKingside);
}

TEST(ChessRules, CastlingQueensideBlack_Test) {
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack);
	
	// Check that e8c8 (queenside castling) is in the move list
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e8c8") != moves.end();
	EXPECT_TRUE(canCastleQueenside);
}

TEST(ChessRules, CastlingBlockedByPiece_Test) {
	// Knight on g1 blocks kingside castling
	chessqdl::Bitboard board("r3k2r/8/8/8/8/8/8/R3K1NR w KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Check that e1g1 (kingside castling) is NOT in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	EXPECT_FALSE(canCastleKingside);
}

TEST(ChessRules, CastlingThroughCheck_Test) {
	// Bishop on a6 attacks d1, castling queenside would move through check
	chessqdl::Bitboard board("4k3/8/b7/8/8/8/8/R3K2R w KQ - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Check that e1c1 (queenside castling) is NOT in the move list (would pass through check on d1)
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_FALSE(canCastleQueenside);
}

TEST(ChessRules, CastlingWhileInCheck_Test) {
	// King is in check, cannot castle
	chessqdl::Bitboard board("4k3/8/8/8/8/4r3/8/R3K2R w KQ - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite);
	
	// Check that neither e1g1 nor e1c1 are in the move list
	bool canCastleKingside = std::find(moves.begin(), moves.end(), "e1g1") != moves.end();
	bool canCastleQueenside = std::find(moves.begin(), moves.end(), "e1c1") != moves.end();
	EXPECT_FALSE(canCastleKingside);
	EXPECT_FALSE(canCastleQueenside);
}

// ============================================================================
// EN PASSANT TESTS
// ============================================================================

TEST(ChessRules, EnPassantCaptureWhite_Test) {
	// Black pawn on e5, white pawn moves e2-e4, black can capture en passant
	chessqdl::Bitboard board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	chessqdl::MoveGenerator generator;
	
	// en passant square is e3 (square 20 in bitboard coordinates)
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack, board.getEnPassantSquare());
	
	// Check that e5e4 (en passant capture) is possible
	bool canEnPassant = std::find(moves.begin(), moves.end(), "e5e4") != moves.end();
	EXPECT_TRUE(canEnPassant);
}

TEST(ChessRules, EnPassantCaptureBlack_Test) {
	// White pawn on d4, black pawn moves d7-d5, white can capture en passant
	chessqdl::Bitboard board("rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1");
	chessqdl::MoveGenerator generator;
	
	// en passant square is d6 (square 43 in bitboard coordinates)
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nWhite, board.getEnPassantSquare());
	
	// Check that e4d5 (en passant capture) is possible
	bool canEnPassant = std::find(moves.begin(), moves.end(), "e4d5") != moves.end();
	EXPECT_TRUE(canEnPassant);
}

TEST(ChessRules, EnPassantNotAvailableAfterOneMove_Test) {
	// En passant should only be available immediately after the pawn's two-square move
	chessqdl::Bitboard board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
	chessqdl::MoveGenerator generator;
	
	auto moves = generator.getPseudoLegalMoves(board.getBitBoards(), chessqdl::nBlack);
	
	// Check that e5e4 (en passant capture) is NOT possible (no en passant square in FEN)
	bool canEnPassant = std::find(moves.begin(), moves.end(), "e5e4") != moves.end();
	EXPECT_FALSE(canEnPassant);
}

// ============================================================================
// CHECK, CHECKMATE, AND STALEMATE TESTS
// ============================================================================

TEST(ChessRules, KingInCheckDetection_Test) {
	// White king in check from black rook
	chessqdl::Engine engine("4k3/8/8/8/8/4r3/8/4K3 w - - 0 1", chessqdl::nWhite, 1, false, true, 42);
	
	EXPECT_TRUE(engine.isKingInCheck(chessqdl::nWhite));
	EXPECT_FALSE(engine.isKingInCheck(chessqdl::nBlack));
}

TEST(ChessRules, BackRankMate_Test) {
	// Classic back rank mate position
	chessqdl::Engine engine("6k1/5ppp/8/8/8/8/8/4R2K b - - 0 1", chessqdl::nBlack, 1, false, true, 42);
	
	EXPECT_TRUE(engine.isCheckmate(chessqdl::nBlack));
}

TEST(ChessRules, SmotheredMate_Test) {
	// Smothered mate with knight
	chessqdl::Engine engine("6rk/5Npp/8/8/8/8/8/7K b - - 0 1", chessqdl::nBlack, 1, false, true, 42);
	
	// King is in check and has no legal moves (smothered by its own pieces)
	EXPECT_TRUE(engine.isKingInCheck(chessqdl::nBlack));
	EXPECT_TRUE(engine.isCheckmate(chessqdl::nBlack));
}

TEST(ChessRules, StalemateDetection_Test) {
	// Classic stalemate position
	chessqdl::Engine engine("k7/8/1Q6/8/8/8/8/7K b - - 0 1", chessqdl::nBlack, 1, false, true, 42);
	
	EXPECT_TRUE(engine.isStalemate(chessqdl::nBlack));
	EXPECT_FALSE(engine.isCheckmate(chessqdl::nBlack));
}

TEST(ChessRules, NotStalemateWhenInCheck_Test) {
	// Cannot be stalemate if in check
	chessqdl::Engine engine("k7/8/8/8/8/8/8/R6K b - - 0 1", chessqdl::nBlack, 1, false, true, 42);
	
	EXPECT_FALSE(engine.isStalemate(chessqdl::nBlack));
	EXPECT_TRUE(engine.isCheckmate(chessqdl::nBlack));
}

TEST(ChessRules, FoolsMate_Test) {
	// Fastest possible checkmate in chess - After 1.f3 e5 2.g4 Qh4#
	chessqdl::Engine engine("rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3", chessqdl::nWhite, 1, false, true, 42);
	
	EXPECT_TRUE(engine.isCheckmate(chessqdl::nWhite));
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
	// Bishop on e2 is pinned by rook on e8, but can capture the rook
	chessqdl::Engine engine("4r3/8/8/8/8/8/4B3/4K3 w - - 0 1", chessqdl::nWhite, 1, false, true, 42);
	
	auto legalMoves = engine.getLegalMoves();
	
	// Bishop can capture the rook along the pin
	bool canCaptureRook = std::find(legalMoves.begin(), legalMoves.end(), "e2e8") != legalMoves.end();
	EXPECT_TRUE(canCaptureRook);
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

TEST(ChessRules, PawnDoubleMoveFroInitialPosition_Test) {
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

TEST(ChessRules, PawnCanOnlyCaptureDigonally_Test) {
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
