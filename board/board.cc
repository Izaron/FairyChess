#include "board.h"

namespace NFairyChess {

TBoard::TBoard(std::size_t columns, std::size_t rows)
    : Columns_{columns}
    , Rows_{rows}
    , BoardPieces_{columns * rows}
{
}

TBoard& TBoard::SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece) {
    BoardPieces_[GetArrayIndex(position)] = boardPiece;
    return *this;
}

TBoardPiece TBoard::GetBoardPiece(TBoardPosition position) const {
    return BoardPieces_[GetArrayIndex(position)];
}

std::optional<TBoardPosition> TBoard::ShiftPosition(TBoardPosition position,
    TBoardPosition deltaPosition) const
{
    // check for overflow with signed values
    int signedColumn = static_cast<int>(position.Column) + static_cast<int>(deltaPosition.Column);
    int signedRow = static_cast<int>(position.Row) + static_cast<int>(deltaPosition.Row);
    if (signedColumn < 0 || signedColumn >= Columns_ ||
            signedRow < 0 || signedRow >= Rows_)
    {
        return {};
    }

    // cast back to unsigned value
    return TBoardPosition{.Column = static_cast<std::size_t>(signedColumn),
                          .Row = static_cast<std::size_t>(signedRow)};
}

std::size_t TBoard::GetArrayIndex(TBoardPosition position) const {
    return position.Column * Rows_ + position.Row;
}

} // namespace NFairyChess
