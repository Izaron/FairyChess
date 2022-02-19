#pragma once

#include <optional>
#include <vector>

#include "board_piece.h"

namespace NFairyChess {

struct TBoardPosition {
    std::size_t Column;
    std::size_t Row;
};

class TBoard {
public:
    struct TBoardPieceWithPosition {
        TBoardPosition Position;
        TBoardPiece BoardPiece;
    };

    template<typename TContainer>
    class TBoardPiecesIterator {
    public:
        using value_type = TBoardPiece;
        using reference = TBoardPieceWithPosition;
        using iterator_category = std::forward_iterator_tag;

    public:
        TBoardPiecesIterator(const TContainer::const_iterator& begin,
                             const TContainer::const_iterator& end,
                             std::size_t rows)
            : BeginIter_{begin}
            , Iter_{begin}
            , EndIter_{end}
            , Rows_{rows}
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
            const std::size_t dist = std::distance(BeginIter_, Iter_);
            TBoardPosition pos{/* col = */ dist / Rows_, /* row = */ dist % Rows_};
            return TBoardPieceWithPosition{/* pos = */ pos, /* boardPiece = */ *Iter_};
        }

    private:
        void SkipUntilNonEmptyPiece() {
            while (Iter_ != EndIter_ && const_cast<TBoardPiece&>(*Iter_).IsEmpty()) {
                ++Iter_;
            }
        }

    private:
        TContainer::const_iterator BeginIter_;
        TContainer::const_iterator Iter_;
        TContainer::const_iterator EndIter_;
        std::size_t Rows_;
    };

public:
    using TBoardPiecesContainer = std::vector<TBoardPiece>;

public:
    TBoard(std::size_t columns = 8, std::size_t rows = 8);

    // board pieces setters and getters
    TBoard& SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece);
    TBoardPiece GetBoardPiece(TBoardPosition position) const;

    // iterator over non-empty board pieces
    TBoardPiecesIterator<TBoardPiecesContainer> begin() const {
        return {BoardPieces_.begin(), BoardPieces_.end(), Rows_};
    }
    TBoardPiecesIterator<TBoardPiecesContainer> end() const {
        return {BoardPieces_.end(), BoardPieces_.end(), Rows_};
    }

    // methods for working with coordinates
    std::size_t GetColumns() const;
    std::size_t GetRows() const;
    std::optional<TBoardPosition> ShiftPosition(TBoardPosition position,
        TBoardPosition deltaPosition) const;
    TBoardPosition InversePosition(TBoardPosition position) const;

private:
    std::size_t GetArrayIndex(TBoardPosition position) const;

private:
    std::size_t Columns_;
    std::size_t Rows_;
    TBoardPiecesContainer BoardPieces_;
};

} // namespace NFairyChess
