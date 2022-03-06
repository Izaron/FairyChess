#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TZebraPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 14;
    static constexpr std::size_t Cost = 300;
    static constexpr std::string_view WhiteDumpStr = "Z";
    static constexpr std::string_view BlackDumpStr = "z";
    static constexpr std::string_view WhiteImageFile = "zebra_white.png";
    static constexpr std::string_view BlackImageFile = "zebra_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TZebraPiece);

} // namespace NFairyChess::NFairyPieces
