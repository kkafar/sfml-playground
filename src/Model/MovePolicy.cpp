#include "MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include "PieceKind.hpp"

MovePolicy::MovePolicy(PieceKind piece_kind) : m_kind(piece_kind) {}

bool MovePolicy::isMoveInChessboardBounds(const Move &move) {
  return move.pos.row >= 0 && move.pos.row < 8 && move.pos.col >= 0 && move.pos.col < 8;
}

bool MovePolicy::isPositionInChessboardBounds(const BoardPosition &pos) {
  return pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8;
}
