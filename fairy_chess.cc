#include "board.h"
#include "pawn_piece.h"

using namespace NFairyChess;

int main() {
    TBoardPiece whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);

    TBoard board;
    board.SetBoardPiece({0, 0}, whitePawn);
}
