#include "engine.hpp"
#include "utils.hpp"
#include "movegen.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace chessqdl;


/**
 * @details Starts a new standard game of chess with the engine as \p color pieces
 */
Engine::Engine(const enumColor color, const int depth, const bool v, const bool p, const std::optional<int> seed) {
    bitboard = Bitboard();
    pieceColor = color;
    depthLevel = depth;
    beVerbose = v;
    pvp = p;
    generator = !seed.has_value()
                    ? std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())
                    : std::default_random_engine(seed.value());
}


/**
 * @details Sets up a game of chess according to the \p fen argument with the engine as \p color pieces
 */
Engine::Engine(const std::string &fen, const enumColor color, const int depth, const bool v, const bool p,
               const std::optional<int> seed) {
    bitboard = Bitboard(fen);
    pieceColor = color;
    toMove = (fen.substr(fen.find(' ') + 1, 1) == "w") ? nWhite : nBlack;
    depthLevel = depth;
    beVerbose = v;
    pvp = p;
    generator = !seed.has_value()
                    ? std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())
                    : std::default_random_engine(seed.value());
}


/**
 * @details Prints the current start of the board to stdout
 */
void Engine::printBoard() const {
    bitboard.printBoard();
}


/**
 * @details Returns Engine::toMove
 */
enumColor Engine::getToMove() const {
    return toMove;
}


/**
 * @details Sets the new max traversal depth of the moves tree to \p nana
 */
void Engine::setDepth(const int n) {
    if (n > 0) {
        std::cout << "New max search depth: " << n << std::endl;
        depthLevel = n;
    }
}


/**
 * @details Main interface to the engine. Allows the player to interact with the engine with the options: <br>
 * <b> print </b> calls Engine::printBoard() and prints the current state of the board to stdout using Unicode symbols <br>
 * <b> move </b> or <b> mv </b> expects a string after the keyword with the move to be made. The move will only be made if a) it's your turn to move the desired pieces and b) the move is valid <br>
 * <b> undo </b> takes back the latest move made. Can take an argument after the keyword to specify the amount of moves to be unmade <br>
 * <b> depth </b> or <b> set_depth </b> specifies the new maximum search depth of the algorithm. The higher the maximum depth, the higher the difficulty of the engine <br>
 * <b> exit </b> or <b> quit </b> exits the game without saving the progress <br>
 */
void Engine::parser() {
    std::string input;

    while (true) {
        if (pieceColor == toMove && !pvp) {
            if (this->beVerbose) std::cout << std::endl << "Searching for the next move..." << std::endl;
            makeMove(getBestMove(depthLevel, pieceColor));
            printBoard();
        }

        std::cout << "> ";
        std::cin >> input;

        if (input == "print" || input == "print_board")
            printBoard();
        else if (input == "move" || input == "mv") {
            // Reads the movement to be made
            std::cin >> input;
            makeMove(input);
            printBoard();
        } else if (input == "undo") {
            int num = 1;
            readInteger(num);
            for (int i = 0; i < num; i++) {
                if (!moveHistory.empty())
                    takeMove();
                else {
                    std::cout << "Move history is empty!" << std::endl;
                    break;
                }
            }
        } else if (input == "restart") {
            while (!moveHistory.empty())
                takeMove();
        } else if (input == "depth" || input == "set_depth") {
            int d = 3;
            readInteger(d);
            setDepth(d);
        } else if (input == "exit" || input == "quit")
            break;
        else if (input == "list") {
            const auto moves = getLegalMoves();
            for (auto &mv: moves)
                std::cout << mv << std::endl;
        } else if (input == "hint") {
            std::cout << getBestMove(depthLevel, toMove) << std::endl;
        } else if (input == "fen") {
            std::cout << getFEN() << std::endl;
        } else if (input == "help") {
            std::cout << "print_board (print for short) - prints out the current state of the board" << std::endl;
            std::cout << "move (mv for short)           - makes a movement if valid. 'move' and 'mv' can be omitted" <<
                    std::endl;
            std::cout <<
                    "set_depth (depth for short)   - specifies the search depth of the minimax algorithm. Used to adjust difficulty of the engine"
                    << std::endl;
            std::cout << "list                          - prints out a list of valid moves in the expected format" <<
                    std::endl;
            std::cout << "hint                          - prints the move that the engine would make" << std::endl;
            std::cout << "fen                           - exports the current board position as a FEN string" << std::endl;
            std::cout <<
                    "undo                          - takes a movement from the stack. Accepts an integer as argument to specify the amount of moves to be taken"
                    << std::endl;
            std::cout << "restart                       - starts a new match with the standard board configuration" <<
                    std::endl;
            std::cout << "help                          - prints out this message with information about valid commands"
                    << std::endl;
            std::cout << "exit (or quit)                - exits the game" << std::endl;
        } else {
            const auto moves = getLegalMoves();
            if (std::find(moves.begin(), moves.end(), input) != moves.end()) {
                makeMove(input, false);
                printBoard();
            } else {
                std::cout << "'" << input << "' is not a valid command." << std::endl;
                // Flushing stdin
                int ch;
                while ((ch = std::cin.get()) != '\n' && ch != EOF);
            }
        }

        // Check for checkmate
        if (isCheckmate(toMove)) {
            const enumColor winner = (toMove == nWhite) ? nBlack : nWhite;
            std::cout << std::endl << "Checkmate! " << ((winner == nWhite) ? "White" : "Black") << " wins" << std::endl;
            break;
        }
        
        // Check for stalemate
        if (isStalemate(toMove)) {
            std::cout << std::endl << "Stalemate! Game is a draw" << std::endl;
            break;
        }

        // TODO: Remove this legacy check once we verify it's not needed
        // Legacy check: This should not happen if legal move generation works correctly
        // but kept as a safety net
        if (bitboard.getKing(nWhite) == 0) {
            std::cout << std::endl << "Game over! Black wins" << std::endl;
            break;
        } else if (bitboard.getKing(nBlack) == 0) {
            std::cout << std::endl << "Game over! White wins" << std::endl;
            break;
        }
    }
}


bool Engine::isKingInCheck(const enumColor color) const {
    const enumColor opponentColor = color == nWhite ? nBlack : nWhite;

    const U64 king = bitboard.getKing(color);
    const U64 underAttack = MoveGenerator::getBishopMoves(bitboard.getBitBoards(), opponentColor) |
                            MoveGenerator::getRookMoves(bitboard.getBitBoards(), opponentColor) |
                            MoveGenerator::getKnightMoves(bitboard.getBitBoards(), opponentColor) |
                            MoveGenerator::getPawnMoves(bitboard.getBitBoards(), opponentColor, 0) |
                            MoveGenerator::getQueenMoves(bitboard.getBitBoards(), opponentColor) |
                            MoveGenerator::getKingMoves(bitboard.getBitBoards(), opponentColor);

    return (king & underAttack) != 0;
}


/**
 * @details Checks if the given color is in checkmate (king is in check and has no legal moves)
 */
bool Engine::isCheckmate(const enumColor color) {
    // Checkmate requires the king to be in check
    if (!isKingInCheck(color)) {
        return false;
    }
    
    // Check if there are any legal moves available
    const enumColor savedToMove = toMove;
    toMove = color;
    const auto legalMoves = getLegalMoves();
    toMove = savedToMove;
    
    // If there are no legal moves and king is in check, it's checkmate
    return legalMoves.empty();
}


/**
 * @details Checks if the given color is in stalemate (king is not in check but has no legal moves)
 */
bool Engine::isStalemate(const enumColor color) {
    // Stalemate requires the king to NOT be in check
    if (isKingInCheck(color)) {
        return false;
    }
    
    // Check if there are any legal moves available
    const enumColor savedToMove = toMove;
    toMove = color;
    const auto legalMoves = getLegalMoves();
    toMove = savedToMove;
    
    // If there are no legal moves and king is not in check, it's stalemate
    return legalMoves.empty();
}


// NOLINTBEGIN(misc-no-recursion)
/**
 * @details Returns the evaluation of the current board state
 */
std::vector<std::string> Engine::getLegalMoves() {
    std::vector<std::string> moves = MoveGenerator::getPseudoLegalMoves(bitboard.getBitBoards(), toMove, bitboard.getEnPassantSquare(), bitboard.getCastlingRights());

    // `toMove` will be updated during the loop, so it is necessary to store it in a variable
    const enumColor currentPlayer = toMove;

    // Simulate move and check if king is in check
    for (auto it = moves.begin(); it != moves.end();) {
        makeMove(*it, false, false);

        if (isKingInCheck(currentPlayer)) {
            it = moves.erase(it);
        } else {
            ++it;
        }

        takeMove();
    }

    return moves;
}


/**
 * @brief Moves a piece from a square to another and updates the bitboards, the move history and the capture history when necessary
 * @param mv  the move to be made
    * @param verify  whether to verify if the move is legal or not. If set to false, the move will be made regardless of its legality
 * @param verbose  whether to print the move made (in algebraic notation) to stdout. This flag is used so that the engine won't flood stdout with all the moves it has made while searching for
 * the optimal one
 */
void Engine::makeMove(std::string mv, const bool verify, const bool verbose) {
    bool isLegal = true;

    if (verify) {
        auto legalMoves = getLegalMoves();
        isLegal = std::find(legalMoves.begin(), legalMoves.end(), mv) != legalMoves.end();
    }

    const enumColor otherPlayer = (toMove == nWhite) ? nBlack : nWhite;

    if (verify & !isLegal)
        std::cout << "Invalid move!" << std::endl;
    else {
        // Source square
        const std::string from = mv.substr(0, 2);
        // Destination square
        const std::string to = mv.substr(2, 2);

        // Iterators to the respective square name
        const auto fromIt = std::find(mapPositions.begin(), mapPositions.end(), from);
        const auto toIt = std::find(mapPositions.begin(), mapPositions.end(), to);

        // Index of the respective square
        const int fromIdx = static_cast<int>(std::distance(mapPositions.begin(), fromIt));
        const int toIdx = static_cast<int>(std::distance(mapPositions.begin(), toIt));

        // Save current en passant square for undo
        enPassantHistory.push(bitboard.getEnPassantSquare());

        // Save current castling rights for undo
        castlingRightsHistory.push(bitboard.getCastlingRights());

        // Type of the piece that is being moved
        enumPiece pieceType = nPawn;

        // It is assumed that the moving piece is a pawn. This loop checks verifies if it's true and if it isn't, it changes the piece type
        for (int i = nPawn; i <= nKing; i++) {
            if (U64 aux = bitboard.getPiecesAt(i) & bitboard.getPieces(toMove); aux.test(fromIdx)) {
                pieceType = static_cast<enumPiece>(i);
                break;
            }
        }

        // Inserts the appropriate character into the algebraic notation string
        switch (pieceType) {
            case nKnight:
                mv.insert(0, "N");
                break;
            case nBishop:
                mv.insert(0, "B");
                break;
            case nRook:
                mv.insert(0, "R");
                break;
            case nQueen:
                mv.insert(0, "Q");
                break;
            case nKing:
                mv.insert(0, "K");
                break;
            default:
                break;
        }

        // If a piece is being captured
        if (bitboard.testBit(otherPlayer, toIdx)) {
            for (int i = nPawn; i <= nKing; i++) {
                if (U64 aux = bitboard.getPiecesAt(i) & bitboard.getPieces(otherPlayer); aux.test(toIdx)) {
                    bitboard.resetBit(i, toIdx);
                    captureHistory.push(static_cast<enumColor>(i));
                    mv.insert(mv.find_first_of("12345678") + 1, "x");
                    break;
                }
            }
            // Removes piece from the board
            bitboard.resetBit(otherPlayer, toIdx);
        }
        // Check if this is an en passant capture
        // En passant: pawn moves diagonally but no piece at destination
        else if (pieceType == nPawn && fromIdx % 8 != toIdx % 8 && bitboard.getEnPassantSquare() == toIdx) {
            // This is an en passant capture
            // The captured pawn is adjacent to the destination square
            int capturedPawnIdx;
            if (toMove == nWhite) {
                // White capturing: captured pawn is south of destination
                capturedPawnIdx = toIdx - 8;
            } else {
                // Black capturing: captured pawn is north of destination
                capturedPawnIdx = toIdx + 8;
            }
            
            // Remove the captured pawn
            bitboard.resetBit(nPawn, capturedPawnIdx);
            bitboard.resetBit(otherPlayer, capturedPawnIdx);
            captureHistory.push(static_cast<enumColor>(nPawn));
            mv.insert(mv.find_first_of("12345678") + 1, "x");
        }

        // Check if this is a castling move
        if (pieceType == nKing && std::abs(toIdx - fromIdx) == 2) {
            // Move the rook as well
            if (toIdx > fromIdx) {
                // Kingside castling (king moves right)
                int rookFromIdx = (toMove == nWhite) ? h1 : h8;
                int rookToIdx = (toMove == nWhite) ? f1 : f8;
                bitboard.resetBit(nRook, rookFromIdx);
                bitboard.resetBit(toMove, rookFromIdx);
                bitboard.setBit(nRook, rookToIdx);
                bitboard.setBit(toMove, rookToIdx);
                mv = "O-O"; // Short castling notation
            } else {
                // Queenside castling (king moves left)
                int rookFromIdx = (toMove == nWhite) ? a1 : a8;
                int rookToIdx = (toMove == nWhite) ? d1 : d8;
                bitboard.resetBit(nRook, rookFromIdx);
                bitboard.resetBit(toMove, rookFromIdx);
                bitboard.setBit(nRook, rookToIdx);
                bitboard.setBit(toMove, rookToIdx);
                mv = "O-O-O"; // Long castling notation
            }
        }

        // Updates bitboards
        bitboard.resetBit(pieceType, fromIdx);
        bitboard.resetBit(toMove, fromIdx);
        bitboard.setBit(pieceType, toIdx);
        bitboard.setBit(toMove, toIdx);

        // If is promotion
        if (isalpha(mv.back()) && pieceType == nPawn) {
            // Promote to queen by default
            enumPiece promoteTo = nQueen;

            if (mv.back() == 'n') promoteTo = nKnight;
            else if (mv.back() == 'b') promoteTo = nBishop;
            else if (mv.back() == 'r') promoteTo = nRook;

            bitboard.setBit(promoteTo, toIdx);
            bitboard.resetBit(pieceType, toIdx);
        }

        // Update castling rights
        // If king moves, lose both castling rights for that color
        if (pieceType == nKing) {
            bitboard.removeCastlingRight(toMove, true);  // kingside
            bitboard.removeCastlingRight(toMove, false); // queenside
        }
        // If rook moves from original square, lose that side's castling right
        if (pieceType == nRook) {
            if (toMove == nWhite) {
                if (fromIdx == h1) bitboard.removeCastlingRight(nWhite, true);
                if (fromIdx == a1) bitboard.removeCastlingRight(nWhite, false);
            } else {
                if (fromIdx == h8) bitboard.removeCastlingRight(nBlack, true);
                if (fromIdx == a8) bitboard.removeCastlingRight(nBlack, false);
            }
        }
        // If rook is captured on its original square, lose that side's castling right
        if (toIdx == h1) bitboard.removeCastlingRight(nWhite, true);
        if (toIdx == a1) bitboard.removeCastlingRight(nWhite, false);
        if (toIdx == h8) bitboard.removeCastlingRight(nBlack, true);
        if (toIdx == a8) bitboard.removeCastlingRight(nBlack, false);

        // Handle en passant square update
        // Clear en passant square by default (it's only valid for one move)
        int newEnPassantSquare = 0;
        
        // Check if this move was a pawn double push (possible en passant)
        if (pieceType == nPawn) {
            int fromRank = fromIdx / 8;
            int toRank = toIdx / 8;
            int fromFile = fromIdx % 8;
            int toFile = toIdx % 8;
            
            // Pawn moved exactly 2 squares vertically and same file
            if (fromFile == toFile && std::abs(toRank - fromRank) == 2) {
                // En passant square is the square the pawn passed through
                // For white moving up (north): middle square = (fromRank + toRank) / 2 * 8 + file
                // For black moving down (south): same calculation
                newEnPassantSquare = ((fromRank + toRank) / 2) * 8 + fromFile;
            }
        }
        
        bitboard.setEnPassantSquare(newEnPassantSquare);

        // Updates the bitboard that contains info about both players
        bitboard.updateBitboard();

        // Move number after the string when appropriate (if ply is even)
        if (ply % 2 == 0)
            mv = std::to_string(ply / 2 + 1) + ". " + mv;

        ++ply;

        // Updates move history
        moveHistory.push(mv);

        toMove = otherPlayer;

        if (isKingInCheck(otherPlayer)) mv.append("+");

        if (verbose)
            std::cout << mv << std::endl;
    }
}

// NOLINTEND(misc-no-recursion)

/**
 * @details Removes the latest entry to the move history and updates the bitboards accordingly.
 */
void Engine::takeMove() {
    if (!moveHistory.empty()) {
        std::string lastMove = moveHistory.top();
        moveHistory.pop();

        if (lastMove.find(' ') != std::string::npos) {
            lastMove = lastMove.substr(lastMove.find(' ') + 1);
        }

        // Remove check indicator if present
        if (!lastMove.empty() && lastMove.back() == '+') {
            lastMove.pop_back();
        }

        const enumColor hasMoved = toMove == nWhite ? nBlack : nWhite;

        // Handle castling
        if (lastMove == "O-O" || lastMove == "O-O-O") {
            bool isKingside = (lastMove == "O-O");
            
            if (hasMoved == nWhite) {
                // Undo white castling
                // Move king back from g1/c1 to e1
                int kingFrom = e1;
                int kingTo = isKingside ? g1 : c1;
                bitboard.resetBit(nKing, kingTo);
                bitboard.resetBit(nWhite, kingTo);
                bitboard.setBit(nKing, kingFrom);
                bitboard.setBit(nWhite, kingFrom);
                
                // Move rook back
                int rookFrom = isKingside ? h1 : a1;
                int rookTo = isKingside ? f1 : d1;
                bitboard.resetBit(nRook, rookTo);
                bitboard.resetBit(nWhite, rookTo);
                bitboard.setBit(nRook, rookFrom);
                bitboard.setBit(nWhite, rookFrom);
            } else {
                // Undo black castling
                int kingFrom = e8;
                int kingTo = isKingside ? g8 : c8;
                bitboard.resetBit(nKing, kingTo);
                bitboard.resetBit(nBlack, kingTo);
                bitboard.setBit(nKing, kingFrom);
                bitboard.setBit(nBlack, kingFrom);
                
                // Move rook back
                int rookFrom = isKingside ? h8 : a8;
                int rookTo = isKingside ? f8 : d8;
                bitboard.resetBit(nRook, rookTo);
                bitboard.resetBit(nBlack, rookTo);
                bitboard.setBit(nRook, rookFrom);
                bitboard.setBit(nBlack, rookFrom);
            }
            
            bitboard.updateBitboard();
            
            // Restore castling rights from history
            if (!castlingRightsHistory.empty()) {
                int prevCastlingRights = castlingRightsHistory.top();
                castlingRightsHistory.pop();
                bitboard.setCastlingRights(prevCastlingRights);
            }
            
            // Restore en passant square from history
            if (!enPassantHistory.empty()) {
                int prevEnPassantSquare = enPassantHistory.top();
                enPassantHistory.pop();
                bitboard.setEnPassantSquare(prevEnPassantSquare);
            }
            
            toMove = hasMoved;
            --ply;
            return;
        }

        enumPiece pieceType = nPawn;
        bool captured = false;

        // Figures out the piece that was moved
        if (lastMove.find_first_of("NBRQK") != std::string::npos) {
            if (lastMove.at(0) == 'N')
                pieceType = nKnight;
            else if (lastMove.at(0) == 'B')
                pieceType = nBishop;
            else if (lastMove.at(0) == 'R')
                pieceType = nRook;
            else if (lastMove.at(0) == 'Q')
                pieceType = nQueen;
            else if (lastMove.at(0) == 'K')
                pieceType = nKing;

            lastMove.erase(0, 1);
        }

        // If a piece was captured, it has to be placed back in the board
        if (lastMove.find('x') != std::string::npos) {
            captured = true;
            lastMove.erase(lastMove.find('x'), 1);
        }

        // Strings with the name of the squares used (source and destination)
        const std::string from = lastMove.substr(0, 2);
        const std::string to = lastMove.substr(2, 2);

        // Iterators of the respective square name
        const auto fromIt = std::find(mapPositions.begin(), mapPositions.end(), from);
        const auto toIt = std::find(mapPositions.begin(), mapPositions.end(), to);

        // Indexes of the respective square name
        const int fromIdx = static_cast<int>(std::distance(mapPositions.begin(), fromIt));
        const int toIdx = static_cast<int>(std::distance(mapPositions.begin(), toIt));

        // Updates bitboards
        bitboard.resetBit(pieceType, toIdx);
        bitboard.resetBit(hasMoved, toIdx);
        bitboard.setBit(pieceType, fromIdx);
        bitboard.setBit(hasMoved, fromIdx);

        // If is promotion
        if (isalpha(lastMove.back()) && pieceType == nPawn) {
            // Promote to queen by default
            enumPiece promoteTo = nQueen;

            if (lastMove.back() == 'n') promoteTo = nKnight;
            else if (lastMove.back() == 'b') promoteTo = nBishop;
            else if (lastMove.back() == 'r') promoteTo = nRook;

            bitboard.resetBit(promoteTo, toIdx);
        }

        // "De-captures" a piece
        if (captured) {
            const enumColor capturedPiece = captureHistory.top();
            captureHistory.pop();
            
            // Check if this was an en passant capture
            // En passant: pawn capture, diagonal move, and previous en passant square matches destination
            int prevEnPassantSquare = enPassantHistory.empty() ? 0 : enPassantHistory.top();
            bool isEnPassant = (pieceType == nPawn && 
                                fromIdx % 8 != toIdx % 8 && 
                                prevEnPassantSquare == toIdx);
            
            if (isEnPassant) {
                // Restore captured pawn to adjacent square, not destination square
                int capturedPawnIdx;
                if (hasMoved == nWhite) {
                    // White moved, so white captured: captured pawn was south of destination
                    capturedPawnIdx = toIdx - 8;
                } else {
                    // Black moved, so black captured: captured pawn was north of destination
                    capturedPawnIdx = toIdx + 8;
                }
                bitboard.setBit(toMove, capturedPawnIdx);
                bitboard.setBit(capturedPiece, capturedPawnIdx);
            } else {
                // Normal capture: restore to destination square
                bitboard.setBit(toMove, toIdx);
                bitboard.setBit(capturedPiece, toIdx);
            }
        }

        bitboard.updateBitboard();

        // Restore castling rights from history
        if (!castlingRightsHistory.empty()) {
            int prevCastlingRights = castlingRightsHistory.top();
            castlingRightsHistory.pop();
            bitboard.setCastlingRights(prevCastlingRights);
        }

        // Restore en passant square from history
        if (!enPassantHistory.empty()) {
            int prevEnPassantSquare = enPassantHistory.top();
            enPassantHistory.pop();
            bitboard.setEnPassantSquare(prevEnPassantSquare);
        }

        toMove = hasMoved;

        --ply;
    }
}


/**
 * @details Performs a recursive search on the moves tree using the minimax algorithm with alpha-beta pruning and returns the best move it has found
 */
std::string Engine::getBestMove(const int depth, const enumColor color) {
    std::string bestMove;
    int nodesVisited = 0;

    auto begin = std::chrono::steady_clock::now();

    alphaBetaMax(intMin, intMax, depth, depth, color, nodesVisited, bestMove);

    auto end = std::chrono::steady_clock::now();

    if (this->beVerbose) {
        std::cout << "Best move found: " << bestMove << std::endl;
        std::cout << "Nodes visited: " << nodesVisited << std::endl;
        std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() <<
                " ms" << std::endl;
    }


    return bestMove;
}


/**
 * @details Minimax implementation
 * @ref https://en.wikipedia.org/wiki/Minimax <br>
 * https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
 */
// NOLINTBEGIN(misc-no-recursion)
int Engine::alphaBetaMax(int alpha, const int beta, const int depth, const int depthLeft, const enumColor color,
                         int &nodesVisited, std::string &bestMove) {
    if (depthLeft == 0)
        return evaluateBoard(bitboard.getBitBoards(), color);

    auto allMoves = MoveGenerator::getPseudoLegalMoves(bitboard.getBitBoards(), color, bitboard.getEnPassantSquare(), bitboard.getCastlingRights());

    std::shuffle(std::begin(allMoves), std::end(allMoves), generator);

    const enumColor enemyColor = (color == nWhite) ? nBlack : nWhite;

    for (const auto &currentMove: allMoves) {
        nodesVisited++;

        makeMove(currentMove, false, false);
        const int score = alphaBetaMin(alpha, beta, depth, depthLeft - 1, enemyColor, nodesVisited, bestMove);
        takeMove();

        if (score >= beta)
            return beta;
        if (score > alpha) {
            alpha = score;
            if (depth == depthLeft)
                bestMove = currentMove;
            //std::cout << "New move found for depth " << depth << " " << currentMove << " score: " << score << std::endl;
        }
    }
    return alpha;
}

// NOLINTEND(misc-no-recursion)


/**
 * @details Minimax implementation
 * @ref https://en.wikipedia.org/wiki/Minimax <br>
 * https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
 */
// NOLINTBEGIN(misc-no-recursion)
int Engine::alphaBetaMin(const int alpha, int beta, const int depth, const int depthLeft, enumColor color,
                         int &nodesVisited, std::string &bestMove) {
    if (depthLeft == 0)
        return -evaluateBoard(bitboard.getBitBoards(), color);

    auto allMoves = MoveGenerator::getPseudoLegalMoves(bitboard.getBitBoards(), color, bitboard.getEnPassantSquare(), bitboard.getCastlingRights());

    std::shuffle(std::begin(allMoves), std::end(allMoves), generator);

    const enumColor enemyColor = (color == nWhite) ? nBlack : nWhite;

    for (auto &currentMove: allMoves) {
        nodesVisited++;

        makeMove(currentMove, false, false);
        const int score = alphaBetaMax(alpha, beta, depth, depthLeft - 1, enemyColor, nodesVisited, bestMove);
        takeMove();

        if (score <= alpha)
            return alpha;
        if (score < beta) {
            beta = score;
        }
    }
    return beta;
}

// NOLINTEND(misc-no-recursion)

/**
 * @details Generates a complete FEN string representing the current game state.
 * Components: piece placement, side to move, castling rights, en passant, halfmove clock, fullmove number
 */
std::string Engine::getFEN() const {
    std::string fen = bitboard.getPiecePlacementFEN();
    fen += ' ';
    
    // Side to move
    fen += (toMove == nWhite) ? 'w' : 'b';
    fen += ' ';
    
    // Castling rights
    fen += bitboard.getCastlingFEN();
    fen += ' ';
    
    // En passant target square
    int epSquare = bitboard.getEnPassantSquare();
    if (epSquare > 0) {
        int file = epSquare % 8;
        int rank = epSquare / 8;
        fen += static_cast<char>('a' + file);
        fen += static_cast<char>('1' + rank);
    } else {
        fen += '-';
    }
    fen += ' ';
    
    // Halfmove clock (reset after captures or pawn moves - we don't track this yet, so always 0)
    fen += '0';
    fen += ' ';
    
    // Fullmove number (1-indexed, increments after each black move)
    // ply is 0-indexed, so fullmove = (ply / 2) + 1
    int fullmove = (ply / 2) + 1;
    fen += std::to_string(fullmove);
    
    return fen;
}
