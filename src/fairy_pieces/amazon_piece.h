#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

// The queen+knight compound
class TAmazonPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 9;
    static constexpr std::size_t Cost = 1300;
    static constexpr std::string_view WhiteDumpStr = "A";
    static constexpr std::string_view BlackDumpStr = "a";
    static constexpr std::string_view WhiteImageFile = "amazon_white.png";
    static constexpr std::string_view BlackImageFile = "amazon_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TAmazonPiece);

} // namespace NFairyChess::NVanillaPieces
