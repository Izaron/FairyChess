#include "board.h"

namespace NFairyChess {

TBoard::TBoard(int columns, int rows)
    : Columns_{columns}
    , Rows_{rows}
    , BoardPieces_{static_cast<std::size_t>(columns * rows)}
{
}

TBoard& TBoard::SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece) {
    BoardPieces_[GetArrayIndex(position)] = boardPiece;
    return *this;
}

TBoardPiece TBoard::GetBoardPiece(TBoardPosition position) const {
    return BoardPieces_[GetArrayIndex(position)];
}

TBoardPiece TBoard::GetBoardPiece(TBoardPosition position, bool isInverted) const {
    if (isInverted) {
        position = InversePosition(position);
    }
    return GetBoardPiece(position);
}

int TBoard::GetColumns() const {
    return Columns_;
}

int TBoard::GetRows() const {
    return Rows_;
}

std::optional<TBoardPosition> TBoard::ShiftPosition(TBoardPosition position,
    TBoardPosition deltaPosition) const
{
    // check for overflow
    int col = position.Column + deltaPosition.Column;
    int row = position.Row + deltaPosition.Row;
    if (col < 0 || col >= Columns_ || row < 0 || row >= Rows_) {
        return {};
    }
    return TBoardPosition{.Column = col, .Row = row};
}

TBoardPosition TBoard::InversePosition(TBoardPosition position) const {
    return TBoardPosition{.Column = Columns_ - 1 - position.Column,
                          .Row = Rows_ - 1 - position.Row};
}

int TBoard::GetArrayIndex(TBoardPosition position) const {
    return position.Column * Rows_ + position.Row;
}

} // namespace NFairyChess
