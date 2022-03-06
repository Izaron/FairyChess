#include "boards_assembler.h"

#include "bishop_piece.h"
#include "king_piece.h"
#include "knight_piece.h"
#include "pawn_piece.h"
#include "queen_piece.h"
#include "rook_piece.h"

#include "amazon_piece.h"
#include "anti_pawn_piece.h"
#include "atomic_pieces.h"
#include "empress_piece.h"
#include "knight_king_piece.h"
#include "mann_piece.h"
#include "princess_piece.h"
#include "zebra_piece.h"
#include "unicorn_piece.h"
#include "grasshopper_piece.h"

using namespace NFairyChess::NVanillaPieces;
using namespace NFairyChess::NFairyPieces;

namespace NFairyChess {

namespace {

TBoardPiece ConstructPawnPiece(TPawnPiece::EMoveStatus moveStatus, EPieceColor color = EPieceColor::White) {
    TPawnPiece pawnPiece;
    pawnPiece.GetMoveStatus().SetValue(moveStatus);
    return TBoardPiece::CreateFromExisting(color, pawnPiece);
}

// vanilla pieces
const auto WhitePawn = TBoardPiece::Create<TPawnPiece>(EPieceColor::White);
const auto WhiteMovedPawn = ConstructPawnPiece(TPawnPiece::EMoveStatus::Moved);
const auto WhiteKnight = TBoardPiece::Create<TKnightPiece>(EPieceColor::White);
const auto WhiteBishop = TBoardPiece::Create<TBishopPiece>(EPieceColor::White);
const auto WhiteRook = TBoardPiece::Create<TRookPiece>(EPieceColor::White);
const auto WhiteQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::White);
const auto WhiteKing = TBoardPiece::Create<TKingPiece>(EPieceColor::White);

const auto BlackPawn = TBoardPiece::Create<TPawnPiece>(EPieceColor::Black);
const auto BlackKnight = TBoardPiece::Create<TKnightPiece>(EPieceColor::Black);
const auto BlackBishop = TBoardPiece::Create<TBishopPiece>(EPieceColor::Black);
const auto BlackRook = TBoardPiece::Create<TRookPiece>(EPieceColor::Black);
const auto BlackQueen = TBoardPiece::Create<TQueenPiece>(EPieceColor::Black);
const auto BlackKing = TBoardPiece::Create<TKingPiece>(EPieceColor::Black);

// fairy pieces
const auto WhiteAntiPawn = TBoardPiece::Create<TAntiPawnPiece>(EPieceColor::White);
const auto WhiteAmazon = TBoardPiece::Create<TAmazonPiece>(EPieceColor::White);
const auto WhiteEmpress = TBoardPiece::Create<TEmpressPiece>(EPieceColor::White);
const auto WhitePrincess = TBoardPiece::Create<TPrincessPiece>(EPieceColor::White);
const auto WhiteMann = TBoardPiece::Create<TMannPiece>(EPieceColor::White);
const auto WhiteKnightKing = TBoardPiece::Create<TKnightKingPiece>(EPieceColor::White);
const auto WhiteZebra = TBoardPiece::Create<TZebraPiece>(EPieceColor::White);
const auto WhiteUnicorn = TBoardPiece::Create<TUnicornPiece>(EPieceColor::White);
const auto WhiteGrasshopper = TBoardPiece::Create<TGrasshopperPiece>(EPieceColor::White);
const auto WhiteAtomicPawn = TBoardPiece::Create<TAtomicPawnPiece>(EPieceColor::White);
const auto WhiteAtomicKnight = TBoardPiece::Create<TAtomicKnightPiece>(EPieceColor::White);
const auto WhiteAtomicBishop = TBoardPiece::Create<TAtomicBishopPiece>(EPieceColor::White);
const auto WhiteAtomicRook = TBoardPiece::Create<TAtomicRookPiece>(EPieceColor::White);
const auto WhiteAtomicQueen = TBoardPiece::Create<TAtomicQueenPiece>(EPieceColor::White);
const auto WhiteAtomicKing = TBoardPiece::Create<TAtomicKingPiece>(EPieceColor::White);

const auto BlackAntiPawn = TBoardPiece::Create<TAntiPawnPiece>(EPieceColor::Black);
const auto BlackAmazon = TBoardPiece::Create<TAmazonPiece>(EPieceColor::Black);
const auto BlackEmpress = TBoardPiece::Create<TEmpressPiece>(EPieceColor::Black);
const auto BlackPrincess = TBoardPiece::Create<TPrincessPiece>(EPieceColor::Black);
const auto BlackMann = TBoardPiece::Create<TMannPiece>(EPieceColor::Black);
const auto BlackKnightKing = TBoardPiece::Create<TKnightKingPiece>(EPieceColor::Black);
const auto BlackZebra = TBoardPiece::Create<TZebraPiece>(EPieceColor::Black);
const auto BlackUnicorn = TBoardPiece::Create<TUnicornPiece>(EPieceColor::Black);
const auto BlackGrasshopper = TBoardPiece::Create<TGrasshopperPiece>(EPieceColor::Black);
const auto BlackAtomicPawn = TBoardPiece::Create<TAtomicPawnPiece>(EPieceColor::Black);
const auto BlackAtomicKnight = TBoardPiece::Create<TAtomicKnightPiece>(EPieceColor::Black);
const auto BlackAtomicBishop = TBoardPiece::Create<TAtomicBishopPiece>(EPieceColor::Black);
const auto BlackAtomicRook = TBoardPiece::Create<TAtomicRookPiece>(EPieceColor::Black);
const auto BlackAtomicQueen = TBoardPiece::Create<TAtomicQueenPiece>(EPieceColor::Black);
const auto BlackAtomicKing = TBoardPiece::Create<TAtomicKingPiece>(EPieceColor::Black);

} // namespace

TBoard TBoardAssembler::AssembleVanillaBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({5, 0}, WhiteBishop)
        .SetBoardPiece({6, 0}, WhiteKnight)
        .SetBoardPiece({7, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleChargeOfTheLightBrigadeBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({1, 0}, WhiteQueen)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({6, 0}, WhiteQueen)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackKnight)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackKnight)
        .SetBoardPiece({3, 7}, BlackKnight)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackKnight)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackKnight)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleHordeBoard() {
    auto board = TBoard{};
    // White pieces (a lot of pawns)
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 8; ++col) {
            board.SetBoardPiece({col, row}, WhitePawn);
        }
    }
    for (int row = 2; row < 4; ++row) {
        for (int col = 0; col < 8; ++col) {
            board.SetBoardPiece({col, row}, WhiteMovedPawn);
        }
    }
    board.SetBoardPiece({1, 4}, WhiteMovedPawn)
        .SetBoardPiece({2, 4}, WhiteMovedPawn)
        .SetBoardPiece({5, 4}, WhiteMovedPawn)
        .SetBoardPiece({6, 4}, WhiteMovedPawn);

    // Black pieces
    board.SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);

    return board;
}

TBoard TBoardAssembler::AssemblePeasantsRevoltBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackKnight)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackKnight)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({4, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleWeakBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({5, 0}, WhiteBishop)
        .SetBoardPiece({6, 0}, WhiteKnight)
        .SetBoardPiece({7, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackKnight)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackKnight)
        .SetBoardPiece({3, 7}, BlackKnight)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackKnight)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackKnight)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn)
        .SetBoardPiece({2, 5}, BlackPawn)
        .SetBoardPiece({5, 5}, BlackPawn)
        .SetBoardPiece({1, 4}, BlackPawn)
        .SetBoardPiece({2, 4}, BlackPawn)
        .SetBoardPiece({3, 4}, BlackPawn)
        .SetBoardPiece({4, 4}, BlackPawn)
        .SetBoardPiece({5, 4}, BlackPawn)
        .SetBoardPiece({6, 4}, BlackPawn);
}

TBoard TBoardAssembler::AssembleBerolinaBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({5, 0}, WhiteBishop)
        .SetBoardPiece({6, 0}, WhiteKnight)
        .SetBoardPiece({7, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhiteAntiPawn)
        .SetBoardPiece({1, 1}, WhiteAntiPawn)
        .SetBoardPiece({2, 1}, WhiteAntiPawn)
        .SetBoardPiece({3, 1}, WhiteAntiPawn)
        .SetBoardPiece({4, 1}, WhiteAntiPawn)
        .SetBoardPiece({5, 1}, WhiteAntiPawn)
        .SetBoardPiece({6, 1}, WhiteAntiPawn)
        .SetBoardPiece({7, 1}, WhiteAntiPawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackAntiPawn)
        .SetBoardPiece({1, 6}, BlackAntiPawn)
        .SetBoardPiece({2, 6}, BlackAntiPawn)
        .SetBoardPiece({3, 6}, BlackAntiPawn)
        .SetBoardPiece({4, 6}, BlackAntiPawn)
        .SetBoardPiece({5, 6}, BlackAntiPawn)
        .SetBoardPiece({6, 6}, BlackAntiPawn)
        .SetBoardPiece({7, 6}, BlackAntiPawn);
}

TBoard TBoardAssembler::AssembleMadKingBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({4, 0}, WhiteAmazon)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleTuttiFruttiBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteEmpress)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteAmazon)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({5, 0}, WhiteQueen)
        .SetBoardPiece({6, 0}, WhitePrincess)
        .SetBoardPiece({7, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackEmpress)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackAmazon)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackQueen)
        .SetBoardPiece({6, 7}, BlackPrincess)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleKnightmateBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteMann)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKnightKing)
        .SetBoardPiece({5, 0}, WhiteBishop)
        .SetBoardPiece({6, 0}, WhiteMann)
        .SetBoardPiece({7, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackMann)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKnightKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackMann)
        .SetBoardPiece({7, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleGrasshopperBoard() {
    auto board = TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteQueen)
        .SetBoardPiece({4, 0}, WhiteKing)
        .SetBoardPiece({5, 0}, WhiteBishop)
        .SetBoardPiece({6, 0}, WhiteKnight)
        .SetBoardPiece({7, 0}, WhiteRook)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackBishop)
        .SetBoardPiece({3, 7}, BlackQueen)
        .SetBoardPiece({4, 7}, BlackKing)
        .SetBoardPiece({5, 7}, BlackBishop)
        .SetBoardPiece({6, 7}, BlackKnight)
        .SetBoardPiece({7, 7}, BlackRook);

    for (int i = 0; i < 8; ++i) {
        board.SetBoardPiece({i, 1}, WhiteGrasshopper)
            .SetBoardPiece({i, 2}, WhitePawn)
            .SetBoardPiece({i, 5}, BlackPawn)
            .SetBoardPiece({i, 6}, BlackGrasshopper);
    }

    return board;
}

TBoard TBoardAssembler::AssembleAtomicBoard() {
    return TBoard{}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteAtomicRook)
        .SetBoardPiece({1, 0}, WhiteAtomicKnight)
        .SetBoardPiece({2, 0}, WhiteAtomicBishop)
        .SetBoardPiece({3, 0}, WhiteAtomicQueen)
        .SetBoardPiece({4, 0}, WhiteAtomicKing)
        .SetBoardPiece({5, 0}, WhiteAtomicBishop)
        .SetBoardPiece({6, 0}, WhiteAtomicKnight)
        .SetBoardPiece({7, 0}, WhiteAtomicRook)
        .SetBoardPiece({0, 1}, WhiteAtomicPawn)
        .SetBoardPiece({1, 1}, WhiteAtomicPawn)
        .SetBoardPiece({2, 1}, WhiteAtomicPawn)
        .SetBoardPiece({3, 1}, WhiteAtomicPawn)
        .SetBoardPiece({4, 1}, WhiteAtomicPawn)
        .SetBoardPiece({5, 1}, WhiteAtomicPawn)
        .SetBoardPiece({6, 1}, WhiteAtomicPawn)
        .SetBoardPiece({7, 1}, WhiteAtomicPawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackAtomicRook)
        .SetBoardPiece({1, 7}, BlackAtomicKnight)
        .SetBoardPiece({2, 7}, BlackAtomicBishop)
        .SetBoardPiece({3, 7}, BlackAtomicQueen)
        .SetBoardPiece({4, 7}, BlackAtomicKing)
        .SetBoardPiece({5, 7}, BlackAtomicBishop)
        .SetBoardPiece({6, 7}, BlackAtomicKnight)
        .SetBoardPiece({7, 7}, BlackAtomicRook)
        .SetBoardPiece({0, 6}, BlackAtomicPawn)
        .SetBoardPiece({1, 6}, BlackAtomicPawn)
        .SetBoardPiece({2, 6}, BlackAtomicPawn)
        .SetBoardPiece({3, 6}, BlackAtomicPawn)
        .SetBoardPiece({4, 6}, BlackAtomicPawn)
        .SetBoardPiece({5, 6}, BlackAtomicPawn)
        .SetBoardPiece({6, 6}, BlackAtomicPawn)
        .SetBoardPiece({7, 6}, BlackAtomicPawn);
}

TBoard TBoardAssembler::AssembleCapablancaBoard() {
    return TBoard{/* columns = */ 10, /* rows = */ 8}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhitePrincess)
        .SetBoardPiece({3, 0}, WhiteBishop)
        .SetBoardPiece({4, 0}, WhiteQueen)
        .SetBoardPiece({5, 0}, WhiteKing)
        .SetBoardPiece({6, 0}, WhiteBishop)
        .SetBoardPiece({7, 0}, WhiteEmpress)
        .SetBoardPiece({8, 0}, WhiteKnight)
        .SetBoardPiece({9, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)
        .SetBoardPiece({8, 1}, WhitePawn)
        .SetBoardPiece({9, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 7}, BlackRook)
        .SetBoardPiece({1, 7}, BlackKnight)
        .SetBoardPiece({2, 7}, BlackPrincess)
        .SetBoardPiece({3, 7}, BlackBishop)
        .SetBoardPiece({4, 7}, BlackQueen)
        .SetBoardPiece({5, 7}, BlackKing)
        .SetBoardPiece({6, 7}, BlackBishop)
        .SetBoardPiece({7, 7}, BlackEmpress)
        .SetBoardPiece({8, 7}, BlackKnight)
        .SetBoardPiece({9, 7}, BlackRook)
        .SetBoardPiece({0, 6}, BlackPawn)
        .SetBoardPiece({1, 6}, BlackPawn)
        .SetBoardPiece({2, 6}, BlackPawn)
        .SetBoardPiece({3, 6}, BlackPawn)
        .SetBoardPiece({4, 6}, BlackPawn)
        .SetBoardPiece({5, 6}, BlackPawn)
        .SetBoardPiece({6, 6}, BlackPawn)
        .SetBoardPiece({7, 6}, BlackPawn)
        .SetBoardPiece({8, 6}, BlackPawn)
        .SetBoardPiece({9, 6}, BlackPawn);
}

TBoard TBoardAssembler::AssembleWildebeestBoard() {
    return TBoard{/* columns = */ 11, /* rows = */ 10}
        // White pieces
        .SetBoardPiece({0, 0}, WhiteRook)
        .SetBoardPiece({1, 0}, WhiteKnight)
        .SetBoardPiece({2, 0}, WhiteBishop)
        .SetBoardPiece({3, 0}, WhiteBishop)
        .SetBoardPiece({4, 0}, WhiteQueen)
        .SetBoardPiece({5, 0}, WhiteKing)
        .SetBoardPiece({6, 0}, WhiteUnicorn)
        .SetBoardPiece({7, 0}, WhiteZebra)
        .SetBoardPiece({8, 0}, WhiteZebra)
        .SetBoardPiece({9, 0}, WhiteKnight)
        .SetBoardPiece({10, 0}, WhiteRook)
        .SetBoardPiece({0, 1}, WhitePawn)
        .SetBoardPiece({1, 1}, WhitePawn)
        .SetBoardPiece({2, 1}, WhitePawn)
        .SetBoardPiece({3, 1}, WhitePawn)
        .SetBoardPiece({4, 1}, WhitePawn)
        .SetBoardPiece({5, 1}, WhitePawn)
        .SetBoardPiece({6, 1}, WhitePawn)
        .SetBoardPiece({7, 1}, WhitePawn)
        .SetBoardPiece({8, 1}, WhitePawn)
        .SetBoardPiece({9, 1}, WhitePawn)
        .SetBoardPiece({10, 1}, WhitePawn)

        // Black pieces
        .SetBoardPiece({0, 9}, BlackRook)
        .SetBoardPiece({1, 9}, BlackKnight)
        .SetBoardPiece({2, 9}, BlackZebra)
        .SetBoardPiece({3, 9}, BlackZebra)
        .SetBoardPiece({4, 9}, BlackUnicorn)
        .SetBoardPiece({5, 9}, BlackKing)
        .SetBoardPiece({6, 9}, BlackQueen)
        .SetBoardPiece({7, 9}, BlackBishop)
        .SetBoardPiece({8, 9}, BlackBishop)
        .SetBoardPiece({9, 9}, BlackKnight)
        .SetBoardPiece({10, 9}, BlackRook)
        .SetBoardPiece({0, 8}, BlackPawn)
        .SetBoardPiece({1, 8}, BlackPawn)
        .SetBoardPiece({2, 8}, BlackPawn)
        .SetBoardPiece({3, 8}, BlackPawn)
        .SetBoardPiece({4, 8}, BlackPawn)
        .SetBoardPiece({5, 8}, BlackPawn)
        .SetBoardPiece({6, 8}, BlackPawn)
        .SetBoardPiece({7, 8}, BlackPawn)
        .SetBoardPiece({8, 8}, BlackPawn)
        .SetBoardPiece({9, 8}, BlackPawn)
        .SetBoardPiece({10, 8}, BlackPawn);
}

} // namespace NFairyChess
