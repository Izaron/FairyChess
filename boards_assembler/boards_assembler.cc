#include "boards_assembler.h"

#include "pawn.h"
#include "knight.h"

namespace NFairyChess {

TBoard TBoardAssembler::AssembleVanillaBoard() {
    const auto whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);
    const auto whiteKnight = TBoardPiece::Create<NVanillaPieces::TKnightPiece>(EPieceColor::White);

    const auto blackPawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::Black);
    const auto blackKnight = TBoardPiece::Create<NVanillaPieces::TKnightPiece>(EPieceColor::Black);

    return TBoard{}
        // white pieces
        // TODO
        .SetBoardPiece({1, 0}, whiteKnight)
        // TODO
        // TODO
        // TODO
        // TODO
        .SetBoardPiece({6, 0}, whiteKnight)
        // TODO
        .SetBoardPiece({0, 1}, whitePawn)
        .SetBoardPiece({1, 1}, whitePawn)
        .SetBoardPiece({2, 1}, whitePawn)
        .SetBoardPiece({3, 1}, whitePawn)
        .SetBoardPiece({4, 1}, whitePawn)
        .SetBoardPiece({5, 1}, whitePawn)
        .SetBoardPiece({6, 1}, whitePawn)
        .SetBoardPiece({7, 1}, whitePawn)

        // black pieces
        // TODO
        .SetBoardPiece({1, 7}, blackKnight)
        // TODO
        // TODO
        // TODO
        // TODO
        .SetBoardPiece({6, 7}, blackKnight)
        // TODO
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
