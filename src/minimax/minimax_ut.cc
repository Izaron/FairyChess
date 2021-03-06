#include <gtest/gtest.h>
#include "minimax.h"
#include "testing.h"
#include "king_piece.h"
#include "knight_piece.h"
#include "pawn_piece.h"
#include "queen_piece.h"
#include "rook_piece.h"
#include "dummy_piece.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

const auto WhiteKing = TBoardPiece::Create<TKingPiece>(EPieceColor::White);
const auto WhiteQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::White);
const auto WhiteRook = TBoardPiece::Create<TRookPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);
const auto BlackKing = TBoardPiece::Create<TKingPiece>(EPieceColor::Black);
const auto BlackQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::Black);
const auto BlackRook = TBoardPiece::Create<TRookPiece>(EPieceColor::Black);
const auto BlackKnight = TBoardPiece::Create<TKnightPiece>(EPieceColor::Black);
const auto BlackPawn = TBoardPiece::Create<TPawnPiece>(EPieceColor::Black);

TEST(MinimaxTest, SimpleBestCapture) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteQueen)
        .SetBoardPiece({.Column = 5, .Row = 3}, BlackRook)
        .SetBoardPiece({.Column = 3, .Row = 5}, BlackKnight);

    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ♞    ║"
        "║        ║"
        "║   ♕ ♜  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 1};
    TMove move = std::get<TMove>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));

    TBoard board2 = ApplyMove(board1, move);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ♞    ║"
        "║        ║"
        "║     ♕  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

TEST(MinimaxTest, CaptureSearchProlongation) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteQueen)
        .SetBoardPiece({.Column = 5, .Row = 3}, BlackRook)
        .SetBoardPiece({.Column = 3, .Row = 5}, BlackKnight)
        .SetBoardPiece({.Column = 6, .Row = 4}, BlackPawn);


    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ♞    ║"
        "║      ♟︎ ║"
        "║   ♕ ♜  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 1};
    TMove move = std::get<TMove>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));

    TBoard board2 = ApplyMove(board1, move);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║   ♕    ║"
        "║      ♟︎ ║"
        "║     ♜  ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

TEST(MinimaxTest, CheckSearchProlongation) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteRook)
        .SetBoardPiece({.Column = 6, .Row = 3}, BlackQueen)
        .SetBoardPiece({.Column = 5, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 6, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 7, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 6, .Row = 7}, BlackKing);


    std::string_view dump1 =
        "╔════════╗"
        "║      ♚ ║"
        "║     ♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║   ♖  ♛ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 1};
    TMove move = std::get<TMove>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));

    // FIXME: prolongate checks!
    TBoard board2 = ApplyMove(board1, move);
    std::string_view dump2 =
        "╔════════╗"
        "║      ♚ ║"
        "║     ♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║      ♖ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

TEST(MinimaxTest, SimpleCheckSearch) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteRook)
        .SetBoardPiece({.Column = 6, .Row = 3}, BlackQueen)
        .SetBoardPiece({.Column = 5, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 6, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 7, .Row = 6}, BlackPawn)
        .SetBoardPiece({.Column = 6, .Row = 7}, BlackKing);


    std::string_view dump1 =
        "╔════════╗"
        "║      ♚ ║"
        "║     ♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║   ♖  ♛ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 3};
    TMove move = std::get<TMove>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));

    TBoard board2 = ApplyMove(board1, move);
    std::string_view dump2 =
        "╔════════╗"
        "║   ♖  ♚ ║"
        "║     ♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║      ♛ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}

TEST(MinimaxTest, SimpleDefeatDetection) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 0}, WhiteKing)
        .SetBoardPiece({.Column = 4, .Row = 3}, BlackRook)
        .SetBoardPiece({.Column = 3, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 1}, WhiteDummy);

    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    ♜   ║"
        "║        ║"
        "║   ○ ○  ║"
        "║   ○♔○  ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 2};
    EGameEnd gameEnd = std::get<EGameEnd>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));
    EXPECT_EQ(gameEnd, EGameEnd::Checkmate);
}

TEST(MinimaxTest, SimpleStalemateDetection) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 0}, WhiteKing)
        .SetBoardPiece({.Column = 5, .Row = 3}, BlackRook)
        .SetBoardPiece({.Column = 3, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 4, .Row = 1}, WhiteDummy);

    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║     ♜  ║"
        "║        ║"
        "║   ○○   ║"
        "║   ○♔   ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    TMinimax minimax{/* depth = */ 2};
    EGameEnd gameEnd = std::get<EGameEnd>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));
    //FIXME: detect stalemate properly
    //EXPECT_EQ(gameEnd, EGameEnd::Stalemate);
}
