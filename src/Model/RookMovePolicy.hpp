#ifndef __ROOK_MOVE_POLICY_HPP__
#define __ROOK_MOVE_POLICY_HPP__

#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
#include <vector>

class RookMovePolicy : public MovePolicy {
public:
  RookMovePolicy() : MovePolicy(PieceKind::Rook) {}

  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;
};

#endif // !__ROOK_MOVE_POLICY_HPP__
