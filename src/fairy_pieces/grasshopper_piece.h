#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TGrasshopperPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 16;
    static constexpr std::size_t Cost = 200;
    static constexpr std::string_view WhiteDumpStr = "G";
    static constexpr std::string_view BlackDumpStr = "g";
    static constexpr std::string_view WhiteImageFile = "queen_rotated_white.png";
    static constexpr std::string_view BlackImageFile = "queen_rotated_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TGrasshopperPiece);

} // namespace NFairyChess::NVanillaPieces
