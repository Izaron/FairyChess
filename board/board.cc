#include "board.h"

namespace NFairyChess {

template<int Columns, int Rows>
TBoard<Columns, Rows>& TBoard<Columns, Rows>::AddBoardPiece(int col, int row, TBoardPiece boardPiece) {
    BoardPieces_[GetArrayIndex(col, row)] = boardPiece;
    return *this;
}

template<int Columns, int Rows>
std::size_t TBoard<Columns, Rows>::GetArrayIndex(int col, int row) {
    return col * Rows + row;
}

} // namespace NFairyChess
