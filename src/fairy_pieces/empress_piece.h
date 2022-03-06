#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

// The rook+knight compound
class TEmpressPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 10;
    static constexpr std::size_t Cost = 900;
    static constexpr std::string_view WhiteDumpStr = "E";
    static constexpr std::string_view BlackDumpStr = "e";
    static constexpr std::string_view WhiteImageFile = "empress_white.png";
    static constexpr std::string_view BlackImageFile = "empress_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TEmpressPiece);

} // namespace NFairyChess::NVanillaPieces
