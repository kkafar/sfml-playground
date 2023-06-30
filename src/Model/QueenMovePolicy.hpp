#ifndef __QUEEN_MOVE_POLICY_HPP__
#define __QUEEN_MOVE_POLICY_HPP__

#include "Model/BishopMovePolicy.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/RookMovePolicy.hpp"
#include "PieceKind.hpp"

class QueenMovePolicy : public MovePolicy {
public:
  QueenMovePolicy() : MovePolicy(PieceKind::Queen) {}

  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;

private:
  BishopMovePolicy m_bishop_delegate;
  RookMovePolicy m_rook_delegate;
};

#endif // !__QUEEN_MOVE_POLICY_HPP__
