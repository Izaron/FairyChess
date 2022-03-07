#include <gtest/gtest.h>
#include "nuclear_missile_piece.h"
#include "queen_piece.h"
#include "pretty_printer.h"
#include "minimax.h"
#include "testing.h"

using namespace NFairyChess;
using namespace NFairyChess::NFairyPieces;
using namespace NFairyChess::NVanillaPieces;

static TBoardPiece ConstructEscalatedNuclearMissile() {
    TNuclearMissilePiece piece;
    piece.GetEscalationStatus().SetValue(TNuclearMissilePiece::EEscalationStatus::Escalated);
    return TBoardPiece::CreateFromExisting(EPieceColor::White, piece);
}

const auto WhiteNuclearMissile = TBoardPiece::Create<TNuclearMissilePiece>(EPieceColor::White);
const auto WhiteNuclearMissileEscalated = ConstructEscalatedNuclearMissile();
const auto BlackQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::Black);

TEST(NuclearMissile, EmptyBoard) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteNuclearMissileEscalated);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║   N    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves, there are only king-like moves
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 8);
}

TEST(NuclearMissile, SingleTarget) {
    auto board = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteNuclearMissileEscalated)
        .SetBoardPiece({.Column = 3, .Row = 6}, BlackQueen);

    // check initial position
    std::string_view dump =
        "╔════════╗"
        "║        ║"
        "║   ♛    ║"
        "║        ║"
        "║        ║"
        "║   N    ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump, board);

    // find moves, there are king-like moves and blast moves around the queen
    TMoveContainer moves;
    GenerateMoves(moves, board, EPieceColor::White);
    EXPECT_EQ(moves.MovesCount, 8 + 9);
}

TEST(NuclearMissile, BestMove) {
    auto board1 = TBoard{}
        .SetBoardPiece({.Column = 3, .Row = 3}, WhiteNuclearMissileEscalated)
        .SetBoardPiece({.Column = 2, .Row = 5}, BlackQueen)
        .SetBoardPiece({.Column = 2, .Row = 6}, BlackQueen)
        .SetBoardPiece({.Column = 2, .Row = 7}, BlackQueen)
        .SetBoardPiece({.Column = 3, .Row = 5}, BlackQueen)
        .SetBoardPiece({.Column = 3, .Row = 6}, BlackQueen)
        .SetBoardPiece({.Column = 3, .Row = 7}, BlackQueen)
        .SetBoardPiece({.Column = 4, .Row = 5}, BlackQueen)
        .SetBoardPiece({.Column = 4, .Row = 6}, BlackQueen)
        .SetBoardPiece({.Column = 4, .Row = 7}, BlackQueen)
        .SetBoardPiece({.Column = 1, .Row = 1}, BlackQueen);

    // check initial position
    std::string_view dump1 =
        "╔════════╗"
        "║  ♛♛♛   ║"
        "║  ♛♛♛   ║"
        "║  ♛♛♛   ║"
        "║        ║"
        "║   N    ║"
        "║        ║"
        "║ ♛      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump1, board1);

    // find best move
    TMinimax minimax{/* depth = */ 1};
    TMove move = std::get<TMove>(minimax.FindBestMoveOrGameEnd(board1, EPieceColor::White));

    TBoard board2 = ApplyMove(board1, move);
    std::string_view dump2 =
        "╔════════╗"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║ ♛      ║"
        "║        ║"
        "╚════════╝";
    CheckDump(dump2, board2);
}
