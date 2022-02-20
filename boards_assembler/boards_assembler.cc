#include "boards_assembler.h"

#include "bishop_piece.h"
#include "knight_piece.h"
#include "pawn_piece.h"
#include "queen_piece.h"
#include "rook_piece.h"

namespace NFairyChess {

TBoard TBoardAssembler::AssembleVanillaBoard() {
    const auto whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);
    const auto whiteKnight = TBoardPiece::Create<NVanillaPieces::TKnightPiece>(EPieceColor::White);
    const auto whiteBishop = TBoardPiece::Create<NVanillaPieces::TBishopPiece>(EPieceColor::White);
    const auto whiteRook = TBoardPiece::Create<NVanillaPieces::TRookPiece>(EPieceColor::White);
    const auto whiteQueen = TBoardPiece::Create<NVanillaPieces::TQueenPiece>(EPieceColor::White);

    const auto blackPawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::Black);
    const auto blackKnight = TBoardPiece::Create<NVanillaPieces::TKnightPiece>(EPieceColor::Black);
    const auto blackBishop = TBoardPiece::Create<NVanillaPieces::TBishopPiece>(EPieceColor::Black);
    const auto blackRook = TBoardPiece::Create<NVanillaPieces::TRookPiece>(EPieceColor::Black);
    const auto blackQueen = TBoardPiece::Create<NVanillaPieces::TQueenPiece>(EPieceColor::Black);

    return TBoard{}
        // white pieces
        .SetBoardPiece({0, 0}, whiteRook)
        .SetBoardPiece({1, 0}, whiteKnight)
        .SetBoardPiece({2, 0}, whiteBishop)
        .SetBoardPiece({3, 0}, whiteQueen)
        // TODO
        .SetBoardPiece({5, 0}, whiteBishop)
        .SetBoardPiece({6, 0}, whiteKnight)
        .SetBoardPiece({7, 0}, whiteRook)
        .SetBoardPiece({0, 1}, whitePawn)
        .SetBoardPiece({1, 1}, whitePawn)
        .SetBoardPiece({2, 1}, whitePawn)
        .SetBoardPiece({3, 1}, whitePawn)
        .SetBoardPiece({4, 1}, whitePawn)
        .SetBoardPiece({5, 1}, whitePawn)
        .SetBoardPiece({6, 1}, whitePawn)
        .SetBoardPiece({7, 1}, whitePawn)

        // black pieces
        .SetBoardPiece({0, 7}, blackRook)
        .SetBoardPiece({1, 7}, blackKnight)
        .SetBoardPiece({2, 7}, blackBishop)
        .SetBoardPiece({3, 7}, blackQueen)
        // TODO
        // TODO
        .SetBoardPiece({5, 7}, blackBishop)
        .SetBoardPiece({6, 7}, blackKnight)
        .SetBoardPiece({7, 7}, blackRook)
        .SetBoardPiece({0, 6}, blackPawn)
        .SetBoardPiece({1, 6}, blackPawn)
        .SetBoardPiece({2, 6}, blackPawn)
        .SetBoardPiece({3, 6}, blackPawn)
        .SetBoardPiece({4, 6}, blackPawn)
        .SetBoardPiece({5, 6}, blackPawn)
        .SetBoardPiece({6, 6}, blackPawn)
        .SetBoardPiece({7, 6}, blackPawn);
}

} // namespace NFairyChess
