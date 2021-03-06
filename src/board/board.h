#pragma once

#include <array>

#include "constants.h"
#include "board_piece.h"

namespace NFairyChess {

struct TBoardPosition {
    int Column;
    int Row;

    bool operator==(const TBoardPosition& rhs) {
        return Column == rhs.Column && Row == rhs.Row;
    }
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
                             int rows)
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
            const int dist = std::distance(BeginIter_, Iter_);
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
        int Rows_;
    };

public:
    using TBoardPiecesContainer = std::array<TBoardPiece, BoardPiecesMaxCount>;

public:
    TBoard(int columns = 8, int rows = 8);

    // board pieces setters and getters
    TBoard& SetBoardPiece(TBoardPosition position, TBoardPiece boardPiece);
    TBoardPiece GetBoardPiece(TBoardPosition position) const;

    // getter with check of inverted position
    TBoardPiece GetBoardPiece(TBoardPosition position, bool isInverted) const;

    // iterator over non-empty board pieces
    TBoardPiecesIterator<TBoardPiecesContainer> begin() const {
        return {BoardPieces_.begin(), BoardPieces_.end(), Rows_};
    }
    TBoardPiecesIterator<TBoardPiecesContainer> end() const {
        return {BoardPieces_.end(), BoardPieces_.end(), Rows_};
    }

    // methods for working with coordinates
    int GetColumns() const { return Columns_; }
    int GetRows() const { return Rows_; }
    bool ShiftPosition(TBoardPosition& position, TBoardPosition deltaPosition) const;
    TBoardPosition InversePosition(TBoardPosition position) const;

private:
    int GetArrayIndex(TBoardPosition position) const;

private:
    int Columns_;
    int Rows_;
    TBoardPiecesContainer BoardPieces_;
};

class TOrientedBoardWrapper {
public:
    TOrientedBoardWrapper(const TBoard& board, bool isInverted)
        : Board_{board}
        , IsInverted_{isInverted}
    {}

    TBoardPiece GetBoardPiece(TBoardPosition position) const {
        return Board_.GetBoardPiece(position, IsInverted_);
    }

    bool ShiftPosition(TBoardPosition& position, TBoardPosition deltaPosition) const {
        return Board_.ShiftPosition(position, deltaPosition);
    }

    int GetColumns() const { return Board_.GetColumns(); }
    int GetRows() const { return Board_.GetRows(); }

private:
    const TBoard& Board_;
    const bool IsInverted_;
};

} // namespace NFairyChess
