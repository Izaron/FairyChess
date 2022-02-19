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

//std::optional<std::pair<std::size_t, std::size_t>>
//TBoard::AddRelativePosition(EPieceColor color, std::size_t currentCol, std::size_t currentRow,
                            //std::size_t deltaCol, std::size_t deltaRow) const
//{
    //int 
//}

std::size_t TBoard::GetArrayIndex(TBoardPosition position) const {
    return position.Column * Rows_ + position.Row;
}

} // namespace NFairyChess
