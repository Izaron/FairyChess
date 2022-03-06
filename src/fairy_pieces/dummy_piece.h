#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TDummyPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 7;
    static constexpr std::size_t Cost = 0;
    static constexpr std::string_view WhiteDumpStr = "○";
    static constexpr std::string_view BlackDumpStr = "●";
    static constexpr std::string_view WhiteImageFile = "<empty>";
    static constexpr std::string_view BlackImageFile = "<empty>";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TDummyPiece);

} // namespace NFairyChess::NFairyPieces
