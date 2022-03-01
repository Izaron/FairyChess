#include <gtest/gtest.h>
#include "boards_assembler.h"
#include "pretty_printer.h"

using namespace NFairyChess;

TEST(BoardsAssemplerTest, VanillaBoard) {
    TBoard board = TBoardAssembler::AssembleVanillaBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, ChargeOfTheLightBrigadeBoard) {
    TBoard board = TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard();

    std::string_view dump =
        "╔════════╗"
        "║♞♞♞♞♚♞♞♞║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║ ♕ ♕♔ ♕ ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, HordeBoard) {
    TBoard board = TBoardAssembler::AssembleHordeBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║ ♙♙  ♙♙ ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "║♙♙♙♙♙♙♙♙║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, PeasantsRevoltBoard) {
    TBoard board = TBoardAssembler::AssemblePeasantsRevoltBoard();

    std::string_view dump =
        "╔════════╗"
        "║ ♞♞ ♚♞♞ ║"
        "║    ♟︎   ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║    ♔   ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, WeakBoard) {
    TBoard board = TBoardAssembler::AssembleWeakBoard();

    std::string_view dump =
        "╔════════╗"
        "║♞♞♞♞♚♞♞♞║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║  ♟︎  ♟︎  ║"
        "║ ♟︎♟︎♟︎♟︎♟︎♟︎ ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, BerolinaBoard) {
    TBoard board = TBoardAssembler::AssembleBerolinaBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, MadKingBoard) {
    TBoard board = TBoardAssembler::AssembleMadKingBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║    A   ║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, TuttiFruttiBoard) {
    TBoard board = TBoardAssembler::AssembleTuttiFruttiBoard();

    std::string_view dump =
        "╔════════╗"
        "║e♞♝a♚♛p♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║E♘♗A♔♕P♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, KnightmateBoard) {
    TBoard board = TBoardAssembler::AssembleKnightmateBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜m♝♛k♝m♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║♖M♗♕K♗M♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, CapablancaBoard) {
    TBoard board = TBoardAssembler::AssembleCapablancaBoard();

    std::string_view dump =
        "╔══════════╗"
        "║♜♞p♝♛♚♝e♞♜║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║          ║"
        "║          ║"
        "║          ║"
        "║          ║"
        "║♙♙♙♙♙♙♙♙♙♙║"
        "║♖♘P♗♕♔♗E♘♖║"
        "╚══════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}
