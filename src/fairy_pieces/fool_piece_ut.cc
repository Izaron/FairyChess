#include <gtest/gtest.h>
#include "fool_piece.h"
#include "dummy_piece.h"
#include "pretty_printer.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;

const auto WhiteFool = TBoardPiece::Create<TFoolPiece>(EPieceColor::White);
const auto WhiteDummy = TBoardPiece::Create<TDummyPiece>(EPieceColor::White);

TEST(Fool, MovesCount) {
    auto board = TBoard{}.SetBoardPiece({.Column = 4, .Row = 3}, WhiteFool);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    F   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 24);
}

TEST(Fool, MovesPosition) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 4, .Row = 3}, WhiteFool)

        .SetBoardPiece({.Column = 5, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 6}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 6}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 7, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 7, .Row = 5}, WhiteDummy)

        .SetBoardPiece({.Column = 3, .Row = 5}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 6}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 6}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 4}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 5}, WhiteDummy)

        .SetBoardPiece({.Column = 5, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 5, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 6, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 7, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 7, .Row = 1}, WhiteDummy)

        .SetBoardPiece({.Column = 3, .Row = 1}, WhiteDummy)
        .SetBoardPiece({.Column = 3, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 0}, WhiteDummy)
        .SetBoardPiece({.Column = 2, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 2}, WhiteDummy)
        .SetBoardPiece({.Column = 1, .Row = 1}, WhiteDummy);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║  ○○ ○○ ║"
        "║ ○ ○ ○ ○║"
        "║ ○○   ○○║"
        "║    F   ║"
        "║ ○○   ○○║"
        "║ ○ ○ ○ ○║"
        "║  ○○ ○○ ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 0);
}
