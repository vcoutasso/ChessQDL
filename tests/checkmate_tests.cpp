#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Engine/engine.hpp"
#include "Engine/bitboard.hpp"

using namespace chessqdl;

// Test basic checkmate with back rank mate
TEST(Checkmate, BackRankMate_Test) {
    // Black rook on a1, white king on h1 surrounded by pawns - checkmate for white
    // Board: "7k/8/8/8/8/8/6PP/r6K w - - 0 1"
    Engine engine("7k/8/8/8/8/8/6PP/r6K w - - 0 1", nWhite, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isCheckmate(nWhite));
    EXPECT_FALSE(engine.isCheckmate(nBlack));
}

// Test checkmate with queen and king
TEST(Checkmate, QueenAndKingMate_Test) {
    // Black king on h8, white queen on g7, white king on f6 delivers checkmate
    // Board: "7k/6Q1/5K2/8/8/8/8/8 b - - 0 1"
    Engine engine("7k/6Q1/5K2/8/8/8/8/8 b - - 0 1", nBlack, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isCheckmate(nBlack));
    EXPECT_FALSE(engine.isCheckmate(nWhite));
}

// Test fool's mate (shortest possible checkmate in chess)
TEST(Checkmate, FoolsMate_Test) {
    // After 1.f3 e5 2.g4 Qh4#
    // Board: "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3"
    Engine engine("rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3", nWhite, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isCheckmate(nWhite));
    EXPECT_FALSE(engine.isCheckmate(nBlack));
}

// Test scholar's mate
TEST(Checkmate, ScholarsMate_Test) {
    // After 1.e4 e5 2.Bc4 Nc6 3.Qh5 Nf6 4.Qxf7#
    // Board: "r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4"
    Engine engine("r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4", nBlack, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isCheckmate(nBlack));
    EXPECT_FALSE(engine.isCheckmate(nWhite));
}

// Test smothered mate
TEST(Checkmate, SmotheredMate_Test) {
    // Black king on h8 surrounded by own pieces, white knight on f7 delivers checkmate
    // Board: "6rk/5Npp/8/8/8/8/8/7K b - - 0 1"
    Engine engine("6rk/5Npp/8/8/8/8/8/7K b - - 0 1", nBlack, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isCheckmate(nBlack));
    EXPECT_FALSE(engine.isCheckmate(nWhite));
}

// Test stalemate with lone king
TEST(Stalemate, LoneKingStalemate_Test) {
    // Black king on h8 has no legal moves, not in check (white queen on g6)
    // Board: "7k/8/6Q1/8/8/8/8/7K b - - 0 1"
    Engine engine("7k/8/6Q1/8/8/8/8/7K b - - 0 1", nBlack, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isStalemate(nBlack));
    EXPECT_FALSE(engine.isStalemate(nWhite));
    EXPECT_FALSE(engine.isCheckmate(nBlack));
}

// Test not stalemate when there are legal moves
TEST(Stalemate, NotStalemateWithMoves_Test) {
    // Standard starting position
    Engine engine(nWhite, 3, false, true, 42);
    
    EXPECT_FALSE(engine.isStalemate(nWhite));
    EXPECT_FALSE(engine.isStalemate(nBlack));
}

// Test not stalemate when in check (would be checkmate)
TEST(Stalemate, NotStalemateWhenInCheck_Test) {
    // Black king on a8 in check from white rook on a1, white king on c7, no escape
    // Board: "k7/2K5/8/8/8/8/8/R7 b - - 0 1"
    Engine engine("k7/2K5/8/8/8/8/8/R7 b - - 0 1", nBlack, 3, false, true, 42);
    
    EXPECT_FALSE(engine.isStalemate(nBlack));
    EXPECT_TRUE(engine.isCheckmate(nBlack));
}

// Test check detection
TEST(Check, KingInCheck_Test) {
    // White king on e1 is in check from black rook on e8
    // Board: "4r2k/8/8/8/8/8/8/4K3 w - - 0 1"
    Engine engine("4r2k/8/8/8/8/8/8/4K3 w - - 0 1", nWhite, 3, false, true, 42);
    
    EXPECT_TRUE(engine.isKingInCheck(nWhite));
    EXPECT_FALSE(engine.isKingInCheck(nBlack));
}

// Test no check
TEST(Check, KingNotInCheck_Test) {
    // Standard starting position
    Engine engine(nWhite, 3, false, true, 42);
    
    EXPECT_FALSE(engine.isKingInCheck(nWhite));
    EXPECT_FALSE(engine.isKingInCheck(nBlack));
}

// Test discovered check doesn't count as check for the moving side
TEST(Check, DiscoveredCheckAfterMove_Test) {
    // Setup where moving a piece creates a discovered check
    // White king on e1, white bishop on e4, black queen on e8
    // If bishop moves, white king would be in check, so such moves should be illegal
    // Board: "4q2k/8/8/8/4B3/8/8/4K3 w - - 0 1"
    Engine engine("4q2k/8/8/8/4B3/8/8/4K3 w - - 0 1", nWhite, 3, false, true, 42);
    
    // King is not currently in check
    EXPECT_FALSE(engine.isKingInCheck(nWhite));
    
    // But moving the bishop should not be in the legal moves (would expose king to check)
    auto legalMoves = engine.getLegalMoves();
    
    // Check that no bishop moves are legal (they would all expose the king)
    bool hasBishopMoves = false;
    for (const auto& move : legalMoves) {
        if (move[0] == 'e' && move[1] == '4') {
            hasBishopMoves = true;
            break;
        }
    }
    EXPECT_FALSE(hasBishopMoves);
}
