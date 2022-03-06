#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TUnicornPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 15;
    static constexpr std::size_t Cost = 600;
    static constexpr std::string_view WhiteDumpStr = "U";
    static constexpr std::string_view BlackDumpStr = "u";
    static constexpr std::string_view WhiteImageFile = "unicorn_white.png";
    static constexpr std::string_view BlackImageFile = "unicorn_black.png";

public:
    void FillMoves(TMoveContext& moveContext);
};

REGISTER_PIECE(TUnicornPiece);

} // namespace NFairyChess::NFairyPieces
