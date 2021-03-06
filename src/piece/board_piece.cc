#include "board_piece.h"

namespace NFairyChess {

namespace {

TStorageType CreateBoardPieceStorage(EPieceColor color, std::size_t pieceId, TStorageType pieceStorage) {
    TBitStorage<TStorageType> result;
    result.GetView<0, 1>().SetValue(color);
    result.GetView<1, 11>().SetValue(pieceId);
    result.GetView<11>().SetValue(pieceStorage);
    return result.GetView().GetValue();
}

} // namespace

TBoardPiece::TBoardPiece()
    : TBitStorage<TStorageType>{0}
{
}

TBoardPiece::TBoardPiece(EPieceColor color, std::size_t pieceId, TStorageType pieceStorage)
    : TBitStorage<TStorageType>{CreateBoardPieceStorage(color, pieceId, pieceStorage)}
{
}

} // namespace NFairyChess
