#ifndef __MOVE_POLICY_HPP__
#define __MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Move.hpp"
#include "Model/Piece.hpp"
#include "PieceKind.hpp"
#include <vector>


class MovePolicy {
public:
  MovePolicy(PieceKind piece_kind);
  [[nodiscard]] inline PieceKind pieceKind() { return m_kind; }

  virtual void availableMoves(const Piece &piece, const Chessboard &board, std::vector<Move> &result) = 0;

private:
  PieceKind m_kind;
};

#endif // !__MOVE_POLICY_HPP__
