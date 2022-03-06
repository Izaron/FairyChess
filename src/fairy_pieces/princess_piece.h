#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

// The bishop+knight compound
class TPrincessPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 11;
    static constexpr std::size_t Cost = 900;
    static constexpr std::string_view WhiteDumpStr = "P";
    static constexpr std::string_view BlackDumpStr = "p";
    static constexpr std::string_view WhiteImageFile = "princess_white.png";
    static constexpr std::string_view BlackImageFile = "princess_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TPrincessPiece);

} // namespace NFairyChess::NVanillaPieces
