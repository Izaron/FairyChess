#pragma once

#include "piece_registry.h"

namespace NFairyChess::NFairyPieces {

class TKnightKingPiece : public TPiece {
public:
    static constexpr std::size_t PieceId = 13;
    static constexpr std::size_t Cost = 20000;
    static constexpr std::size_t IsRoyal = true;
    static constexpr std::string_view WhiteDumpStr = "K";
    static constexpr std::string_view BlackDumpStr = "k";
    static constexpr std::string_view WhiteImageFile = "knight_king_white.png";
    static constexpr std::string_view BlackImageFile = "knight_king_black.png";

public:
    void FillMoves(TMoveContext moveContext);
};

REGISTER_PIECE(TKnightKingPiece);

} // namespace NFairyChess::NFairyPieces
