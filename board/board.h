#pragma once

#include <vector>

#include "board_piece.h"

namespace NFairyChess {

class TBoard {
public:
    TBoard(std::size_t columns = 8, std::size_t rows = 8);
    TBoard& SetBoardPiece(int col, int row, TBoardPiece boardPiece);
    TBoardPiece GetBoardPiece(int col, int row) const;

    decltype(auto) begin() const {
        return BoardPieces_.begin();
    }

    decltype(auto) end() const {
        return BoardPieces_.end();
    }

private:
    std::size_t GetArrayIndex(int col, int row) const;

private:
    std::size_t Columns_;
    std::size_t Rows_;
    std::vector<TBoardPiece> BoardPieces_;
};

} // namespace NFairyChess
