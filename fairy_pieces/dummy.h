#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TDummyPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 7;
    static constexpr std::size_t Cost = 0;
    static constexpr std::string_view WhiteDumpStr = "○";
    static constexpr std::string_view BlackDumpStr = "●";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TDummyPiece);

} // namespace NFairyChess::NFairyPieces
