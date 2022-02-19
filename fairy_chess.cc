#include "board.h"
#include "pawn.h"

using namespace NFairyChess;

int main() {
    TBoardPiece whitePawn = TBoardPiece::Create<NVanillaPieces::TPawnPiece>(EPieceColor::White);

    TBoard board;
    board.AddBoardPiece(0, 0, whitePawn);
}
