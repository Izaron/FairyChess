#pragma once

#include <vector>

#include "board_piece.h"

namespace NFairyChess {

class TBoard {
public:
    template<typename TContainer>
    class TBoardPiecesIterator {
    public:
        using value_type = TBoardPiece;
        using pointer = const value_type*;
        using reference = const value_type&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

    public:
        TBoardPiecesIterator(const TContainer::const_iterator& iter, const TContainer::const_iterator& end)
            : Iter_{iter}
            , EndIter_{end}
        {
            SkipUntilNonEmptyPiece();
        }

        bool operator==(const TBoardPiecesIterator& other) const {
            return Iter_ == other.Iter_;
        }

        TBoardPiecesIterator& operator++() {
            ++Iter_;
            SkipUntilNonEmptyPiece();
            return *this;
        }

        reference operator*() const {
            return *Iter_;
        }

        pointer operator->() const {
            return &*Iter_;
        }

    private:
        void SkipUntilNonEmptyPiece() {
            while (Iter_ != EndIter_ && const_cast<TBoardPiece&>(*Iter_).IsEmpty()) {
                ++Iter_;
            }
        }

    private:
        TContainer::const_iterator Iter_;
        TContainer::const_iterator EndIter_;
    };

public:
    using TBoardPiecesContainer = std::vector<TBoardPiece>;

public:
    TBoard(std::size_t columns = 8, std::size_t rows = 8);
    TBoard& SetBoardPiece(std::size_t col, std::size_t row, TBoardPiece boardPiece);
    TBoardPiece GetBoardPiece(std::size_t col, std::size_t row) const;

    // iterator over non-empty board pieces
    TBoardPiecesIterator<TBoardPiecesContainer> begin() const {
        return {BoardPieces_.begin(), BoardPieces_.end()};
    }
    TBoardPiecesIterator<TBoardPiecesContainer> end() const {
        return {BoardPieces_.end(), BoardPieces_.end()};
    }

private:
    std::size_t GetArrayIndex(std::size_t col, std::size_t row) const;

private:
    std::size_t Columns_;
    std::size_t Rows_;
    TBoardPiecesContainer BoardPieces_;
};

} // namespace NFairyChess
