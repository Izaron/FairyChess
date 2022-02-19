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

TEST(Pawn, SingleWhitePiece) {
    const auto whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);
    auto board1 = TBoard{}.SetBoardPiece({.Column = 1, .Row = 1}, whitePawn);

    // check initial position
    std::string_view dump1 =
        "        "
        "        "
        "        "
        "        "
        "        "
        "        "
        " P      "
        "        ";
    CheckDump(dump1, board1);

    // find moves
    TMoveContainer moves = GenerateMoves(board1, EPieceColor::White);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check position
    auto board2 = ApplyMove(board1, moves[0]);
    std::string_view dump2 =
        "        "
        "        "
        "        "
        "        "
        "        "
        " P      "
        "        "
        "        ";
    CheckDump(dump2, board2);
}

TEST(Pawn, SingleBlackPiece) {
    const auto blackPawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::Black);
    auto board1 = TBoard{}.SetBoardPiece({.Column = 6, .Row = 6}, blackPawn);

    // check initial position
    std::string_view dump1 =
        "        "
        "      p "
        "        "
        "        "
        "        "
        "        "
        "        "
        "        ";
    CheckDump(dump1, board1);

    // find moves
    TMoveContainer moves = GenerateMoves(board1, EPieceColor::Black);
    EXPECT_EQ(moves.size(), 1);

    // apply move and check position
    auto board2 = ApplyMove(board1, moves[0]);
    std::string_view dump2 =
        "        "
        "        "
        "      p "
        "        "
        "        "
        "        "
        "        "
        "        ";
    CheckDump(dump2, board2);
}
