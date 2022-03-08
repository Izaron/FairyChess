#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TChampionPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 25;
    static constexpr std::size_t Cost = 300;
    static constexpr std::string_view WhiteDumpStr = "C";
    static constexpr std::string_view BlackDumpStr = "c";
    static constexpr std::string_view WhiteImageFile = "champion_white.png";
    static constexpr std::string_view BlackImageFile = "champion_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TChampionPiece);

} // namespace NFairyChess::NFairyPieces
