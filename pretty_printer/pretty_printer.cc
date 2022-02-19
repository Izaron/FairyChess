#include "pretty_printer.h"
#include "piece_registry.h"

#include <ostream>

namespace NFairyChess {

void DumpBoard(const TBoard& board, std::ostream& os, bool useNewline) {
    for (int r = board.GetRows() - 1; r >= 0; --r) {
        for (int c = 0; c < board.GetColumns(); ++c) {
            TBoardPiece boardPiece = board.GetBoardPiece({.Column = c, .Row = r});

            if (const TPieceInfo* pieceInfo = TPieceRegistry::GetPieceInfo(boardPiece.GetPieceId())) {
                char dumpSymbol = pieceInfo->DumpSymbol;
                if (boardPiece.GetColor() == EPieceColor::Black) {
                    dumpSymbol = tolower(dumpSymbol);
                }
                os << dumpSymbol;
            } else {
                // empty square
                os << ' ';
            }
        }

        if (useNewline) {
            os << '\n';
        }
    }
}

} // namespace NFairyChess
