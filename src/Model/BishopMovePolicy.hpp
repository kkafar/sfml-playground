#ifndef __BISHOP_MOVE_POLICY_HPP__
#define __BISHOP_MOVE_POLICY_HPP__

#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
class BishopMovePolicy : public MovePolicy {
public: 
  BishopMovePolicy() : MovePolicy(PieceKind::Bishop) {}

  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;
};

#endif // !__BISHOP_MOVE_POLICY_HPP__
