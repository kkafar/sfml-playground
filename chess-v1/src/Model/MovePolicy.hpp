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

  virtual void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) = 0;

  /// All Moves that COULD BE an attack (but in current board situation they might be normal moves as well).
  virtual void attackMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
    allMoves(piece, board, result);
  }

protected:
  [[nodiscard]] bool isMoveInChessboardBounds(const Move &move);
  [[nodiscard]] bool isPositionInChessboardBounds(const BoardPosition &pos);
  [[nodiscard]] Move::Kind classifyMove(const Piece &piece, Chessboard &board, const BoardPosition &pos);

private:
  PieceKind m_kind;
};

#endif // !__MOVE_POLICY_HPP__
