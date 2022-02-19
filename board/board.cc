#include "board.h"

namespace NFairyChess {

TBoard::TBoard(std::size_t columns, std::size_t rows)
    : Columns_{columns}
    , Rows_{rows}
    , BoardPieces_{columns * rows}
{
}

TBoard& TBoard::SetBoardPiece(int col, int row, TBoardPiece boardPiece) {
    BoardPieces_[GetArrayIndex(col, row)] = boardPiece;
    return *this;
}

TBoardPiece TBoard::GetBoardPiece(int col, int row) const {
    return BoardPieces_[GetArrayIndex(col, row)];
}

std::size_t TBoard::GetArrayIndex(int col, int row) const {
    return col * Rows_ + row;
}

} // namespace NFairyChess
