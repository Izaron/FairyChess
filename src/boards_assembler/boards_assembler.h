#pragma once

#include "board.h"

namespace NFairyChess {

struct TBoardAssembler {
    // vanilla board
    static TBoard AssembleVanillaBoard();

    // standard board but different number of pieces
    static TBoard AssembleChargeOfTheLightBrigadeBoard();
    static TBoard AssembleHordeBoard();
    static TBoard AssemblePeasantsRevoltBoard();
    static TBoard AssembleWeakBoard();
    
    // standard board with fairy pieces
    static TBoard AssembleBerolinaBoard();
    static TBoard AssembleMadKingBoard();
    static TBoard AssembleTuttiFruttiBoard();
    static TBoard AssembleKnightmateBoard();
    static TBoard AssembleGrasshopperBoard();

    // non-standard boards
    static TBoard AssembleCapablancaBoard();
    static TBoard AssembleWildebeestBoard();
};

} // namespace NFairyChess
