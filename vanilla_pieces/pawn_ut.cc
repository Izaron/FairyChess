#include <gtest/gtest.h>
#include "pawn.h"
#include "pretty_printer.h"

using namespace NFairyChess;
using namespace NFairyChess::NVanillaPieces;

static void CheckDump(std::string_view dump, const TBoard& board) {
    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

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

std::unordered_set<std::string> CollectBoardDumps(const TMoveContainer& moves, const TBoard& board) {
    std::unordered_set<std::string> set;
    for (const auto& move : moves) {
        TBoard newBoard = ApplyMove(board, move);
        std::stringstream ss;
        DumpBoard(newBoard, ss);
        set.insert(ss.str());
    }
    return set;
}

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
