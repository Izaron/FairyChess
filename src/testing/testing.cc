#include "testing.h"
#include "pretty_printer.h"

#include <gtest/gtest.h>

using namespace NFairyChess::NVanillaPieces;

namespace NFairyChess {

void CheckDump(std::string_view dump, const TBoard& board) {
    std::stringstream ss;
    DumpBoard(board, ss);
    EXPECT_STREQ(dump.data(), ss.str().data());
}

std::unordered_set<std::string> CollectBoardDumps(const TMoveContainer& moves, const TBoard& board) {
    std::unordered_set<std::string> set;
    for (std::size_t i = 0; i < moves.MovesCount; ++i) {
        const auto& move = moves.Moves[i];
        TBoard newBoard = ApplyMove(board, move);
        std::stringstream ss;
        DumpBoard(newBoard, ss);
        set.insert(ss.str());
    }
    return set;
}

TBoardPiece ConstructPawnPiece(TPawnPiece::EMoveStatus moveStatus, EPieceColor color) {
    TPawnPiece pawnPiece;
    pawnPiece.GetMoveStatus().SetValue(moveStatus);
    return TBoardPiece::CreateFromExisting(color, pawnPiece);
}

} // namespace NFairyChess
