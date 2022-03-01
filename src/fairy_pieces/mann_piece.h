#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TMannPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 12;
    static constexpr std::size_t Cost = 150;
    static constexpr std::string_view WhiteDumpStr = "M";
    static constexpr std::string_view BlackDumpStr = "m";
    static constexpr std::string_view WhiteImageFile = "king_rotated_white.png";
    static constexpr std::string_view BlackImageFile = "king_rotated_black.png";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TMannPiece);

} // namespace NFairyChess::NVanillaPieces
