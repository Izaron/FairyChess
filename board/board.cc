#include "board.h"

namespace NFairyChess {

TBoard::TBoard(std::size_t columns, std::size_t rows)
    : Columns_{columns}
    , Rows_{rows}
    , BoardPieces_{columns * rows}
{
}

TBoard& TBoard::SetBoardPiece(std::size_t col, std::size_t row, TBoardPiece boardPiece) {
    BoardPieces_[GetArrayIndex(col, row)] = boardPiece;
    return *this;
}

TBoardPiece TBoard::GetBoardPiece(std::size_t col, std::size_t row) const {
    return BoardPieces_[GetArrayIndex(col, row)];
}

std::size_t TBoard::GetArrayIndex(std::size_t col, std::size_t row) const {
    return col * Rows_ + row;
}

} // namespace NFairyChess
