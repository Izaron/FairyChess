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

TEST(BoardsAssemplerTest, GrasshopperBoard) {
    TBoard board = TBoardAssembler::AssembleGrasshopperBoard();

    std::string_view dump =
        "╔════════╗"
        "║♜♞♝♛♚♝♞♜║"
        "║gggggggg║"
        "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
        "║        ║"
        "║        ║"
        "║♙♙♙♙♙♙♙♙║"
        "║GGGGGGGG║"
        "║♖♘♗♕♔♗♘♖║"
        "╚════════╝";

    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

TEST(BoardsAssemplerTest, AtomicBoard) {
    TBoard board = TBoardAssembler::AssembleAtomicBoard();

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

TEST(BoardsAssemplerTest, CapablancaBoard) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 8 * 10) {
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
}

TEST(BoardsAssemplerTest, WildebeestBoard) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 11 * 10) {
        TBoard board = TBoardAssembler::AssembleWildebeestBoard();

        std::string_view dump =
            "╔═══════════╗"
            "║♜♞zzu♚♛♝♝♞♜║"
            "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
            "║           ║"
            "║           ║"
            "║           ║"
            "║           ║"
            "║           ║"
            "║           ║"
            "║♙♙♙♙♙♙♙♙♙♙♙║"
            "║♖♘♗♗♕♔UZZ♘♖║"
            "╚═══════════╝";

        std::stringstream ss;
        DumpBoard(board, ss);
        EXPECT_STREQ(dump.data(), ss.str().data());
    }
}

TEST(BoardsAssemplerTest, StratomicBoard) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 10 * 10) {
        TBoard board = TBoardAssembler::AssembleStratomicBoard();

        std::string_view dump =
            "╔══════════╗"
            "║          ║"
            "║n♜♞♝♛♚♝♞♜n║"
            "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
            "║          ║"
            "║          ║"
            "║          ║"
            "║          ║"
            "║♙♙♙♙♙♙♙♙♙♙║"
            "║N♖♘♗♕♔♗♘♖N║"
            "║          ║"
            "╚══════════╝";

        std::stringstream ss;
        DumpBoard(board, ss);
        EXPECT_STREQ(dump.data(), ss.str().data());
    }
}

TEST(BoardsAssemplerTest, ReallyBigBoard) {
    if constexpr (std::tuple_size_v<TBoard::TBoardPiecesContainer> >= 16 * 16) {
        TBoard board = TBoardAssembler::AssembleReallyBigBoard();

        std::string_view dump =
            "╔════════════════╗"
            "║♜♞wc♝dp♛♚ef♝cw♞♜║"
            "║♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎♟︎║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║                ║"
            "║♙♙♙♙♙♙♙♙♙♙♙♙♙♙♙♙║"
            "║♖♘WC♗DP♕♔EF♗CW♘♖║"
            "╚════════════════╝";

        std::stringstream ss;
        DumpBoard(board, ss);
        EXPECT_STREQ(dump.data(), ss.str().data());
    }
}
