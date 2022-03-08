#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TWizardPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 24;
    static constexpr std::size_t Cost = 300;
    static constexpr std::string_view WhiteDumpStr = "W";
    static constexpr std::string_view BlackDumpStr = "w";
    static constexpr std::string_view WhiteImageFile = "wizard_white.png";
    static constexpr std::string_view BlackImageFile = "wizard_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TWizardPiece);

} // namespace NFairyChess::NFairyPieces
