#ifndef __PAWN_MOVE_POLICY_HPP__
#define __PAWN_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include "PieceKind.hpp"
#include <array>

class PawnMovePolicy : public MovePolicy {
public:  
  PawnMovePolicy(PlayerKind piece_color);

  /// Calculates all valid move-to positions for the figure from the given position
  /// and puts the result in provided vector. Make sure (or not) that the vector is empty
  /// before you pass it into this function.
  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;
  void attackMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;

private:
  PlayerKind m_pawn_color;
  BoardPosition m_normal_move_offset;
  int m_initial_row;
  std::array<BoardPosition, 2> m_attack_move_offsets;

  bool isInInitialRow(const Piece &piece);
};

#endif // !__PAWN_MOVE_POLICY_HPP__
