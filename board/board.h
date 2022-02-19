#pragma once

#include <array>

#include "board_piece.h"

namespace NFairyChess {

template<int Columns = 8, int Rows = 8>
class TBoard {
public:
    TBoard& AddBoardPiece(int col, int row, TBoardPiece boardPiece);

private:
    std::size_t GetArrayIndex(int col, int row);

private:
    std::array<TBoardPiece, Columns * Rows> BoardPieces_;
};

template class TBoard<>;

using TBoard8x8 = TBoard<>; // standard 8x8 board

} // namespace NFairyChess
