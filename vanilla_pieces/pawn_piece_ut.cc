#include <gtest/gtest.h>
#include "pawn_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;

static TBoardPiece ConstructPawnPiece(TPawnPiece::EMoveStatus moveStatus = TPawnPiece::EMoveStatus::NotMoved,
                                      EPieceColor color = EPieceColor::White)
{
    TPawnPiece pawnPiece;
    pawnPiece.GetMoveStatus().SetValue(moveStatus);
    return TBoardPiece::CreateFromExisting(color, pawnPiece);
}

const auto WhitePawn = ConstructPawnPiece();
const auto WhiteMovedPawn = ConstructPawnPiece(TPawnPiece::EMoveStatus::Moved);
const auto BlackPawn = ConstructPawnPiece(TPawnPiece::EMoveStatus::NotMoved, EPieceColor::Black);
const auto BlackMovedPawn = ConstructPawnPiece(TPawnPiece::EMoveStatus::Moved, EPieceColor::Black);

TEST(Pawn, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 1, .Row = 1}, WhitePawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 2);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

// Checking that black pieces have mirroring behaviour
TEST(Pawn, SingleBlackPiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 6, .Row = 6}, BlackPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║      ♟︎ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves = GenerateMoves(board, EPieceColor::Black);
    EXPECT_EQ(moves.size(), 2);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║      ♟︎ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║      ♟︎ ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(Pawn, BlockedByFriendlyPiece) {
    // Check that piece can't go forward if there is another piece there
    auto board = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 1}, WhitePawn)
        .SetBoardPiece({.Column = 1, .Row = 2}, WhiteMovedPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // check that there is only one move possible
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(Pawn, BlockedByEnemyPiece) {
    // Check that piece can't go forward if there is another piece there
    auto board = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 2}, WhiteMovedPawn)
        .SetBoardPiece({.Column = 1, .Row = 3}, BlackMovedPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♟︎      ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // check that there are no moves possible
    EXPECT_EQ(GenerateMoves(board, EPieceColor::White).size(), 0);
    EXPECT_EQ(GenerateMoves(board, EPieceColor::Black).size(), 0);
}

TEST(Pawn, OnlyOneDoubleMove) {
    // Check that pawn can jump two squares only once
    auto board = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 1}, WhitePawn);

    // check that there are two moves possible
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 2);

    // check that after any move there will be only one move possible0
    for (const TMove& move : moves) {
        TBoard newBoard = ApplyMove(board, move);
        TMoveContainer newMoves = GenerateMoves(newBoard, EPieceColor::White);
        EXPECT_EQ(newMoves.size(), 1);
    }
}

TEST(Pawn, SimpleCapturing) {
    // Check that piece can capture diagonally
    auto board = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 2}, WhiteMovedPawn)
        .SetBoardPiece({.Column = 2, .Row = 3}, BlackMovedPawn)
        .SetBoardPiece({.Column = 0, .Row = 3}, BlackMovedPawn);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♟︎ ♟︎     ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // check that there are three moves possible: two captures and one move
    TMoveContainer moves = GenerateMoves(board, EPieceColor::White);
    EXPECT_EQ(moves.size(), 3);

    // apply moves and check dump
    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙ ♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♟︎ ♙     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♟︎♙♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves, board));
}

TEST(Pawn, EnPassantImmediateCapturing) {
    // Check that piece can capture en passant
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 1, .Row = 4}, WhiteMovedPawn)
        .SetBoardPiece({.Column = 2, .Row = 6}, BlackPawn);

    // check initial position
    std::string_view dump1 =
        "╔════════╗"
        "║        ║"
        "║  ♟︎     ║"
        "║        ║"
        "║ ♙      ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    // check that black pawn can move one or two squares forward
    TMoveContainer moves1 = GenerateMoves(board1, EPieceColor::Black);
    EXPECT_EQ(moves1.size(), 2);

    // find board where the black pawn moves two squares forward
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♙♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    std::optional<TBoard> board2;
    for (const TMove& move : moves1) {
        TBoard nextBoard = ApplyMove(board1, move);
        std::stringstream ss;
        DumpBoard(nextBoard, ss);
        if (ss.str().data() == dump2) {
            board2 = nextBoard;
        }
    }
    EXPECT_TRUE(board2);

    // check that white pawn have two moves
    TMoveContainer moves2 = GenerateMoves(*board2, EPieceColor::White);
    EXPECT_EQ(moves2.size(), 2);

    std::unordered_set<std::string> set;
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║ ♙      ║"
        "║  ♟︎     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    set.insert(
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║  ♙     ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝"
    );
    EXPECT_EQ(set, CollectBoardDumps(moves2, *board2));
}
