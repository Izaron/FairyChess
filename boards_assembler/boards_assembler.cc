#include "boards_assembler.h"

#include "pawn.h"

namespace NFairyChess {

TBoard8x8 TBoardAssembler::AssembleVanillaBoard() {
    const auto whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);
    const auto blackPawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::Black);

    return TBoard8x8{}
        // white pawns
        .AddBoardPiece(0, 1, whitePawn)
        .AddBoardPiece(1, 1, whitePawn)
        .AddBoardPiece(2, 1, whitePawn)
        .AddBoardPiece(3, 1, whitePawn)
        .AddBoardPiece(4, 1, whitePawn)
        .AddBoardPiece(5, 1, whitePawn)
        .AddBoardPiece(6, 1, whitePawn)
        .AddBoardPiece(7, 1, whitePawn)
        // black pawns
        .AddBoardPiece(0, 6, blackPawn)
        .AddBoardPiece(1, 6, blackPawn)
        .AddBoardPiece(2, 6, blackPawn)
        .AddBoardPiece(3, 6, blackPawn)
        .AddBoardPiece(4, 6, blackPawn)
        .AddBoardPiece(5, 6, blackPawn)
        .AddBoardPiece(6, 6, blackPawn)
        .AddBoardPiece(7, 6, blackPawn);
}

} // namespace NFairyChess
