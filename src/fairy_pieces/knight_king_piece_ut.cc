#include <gtest/gtest.h>
#include "knight_king_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteKnightKing = TBoardPiece::Create<TKnightKingPiece>(EPieceColor::White);

TEST(KnightKing, SingleWhitePiece) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteKnightKing);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    K   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 8);
}
