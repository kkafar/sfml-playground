#ifndef __MOVE_POLICY_HPP__
#define __MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Move.hpp"
#include "PieceKind.hpp"
#include <vector>

class Chessboard;
class Piece;

class MovePolicy {
public:
  MovePolicy(PieceKind piece_kind);
  [[nodiscard]] inline PieceKind pieceKind() { return m_kind; }

  virtual void allMoves(const Piece &piece, const Chessboard &board, std::vector<Move> &result) = 0;

private:
  PieceKind m_kind;
};

#endif // !__MOVE_POLICY_HPP__
