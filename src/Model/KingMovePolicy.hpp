#ifndef __KING_MOVE_POLICY_HPP__
#define __KING_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Move.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include "PieceKind.hpp"
#include "SFML/Config.hpp"
#include <array>
#include <vector>

class KingMovePolicy : public MovePolicy {
public:
  KingMovePolicy(const PlayerKind piece_color);

  void allMoves(const Piece &piece, Chessboard &board,
                std::vector<Move> &result) override;

private:
  constexpr static std::array<BoardPosition, 8> s_offsets{
      BoardPosition{-1, -1}, BoardPosition{-1, 0}, BoardPosition{-1, 1},
      BoardPosition{0, -1},  BoardPosition{0, 1},  BoardPosition{1, -1},
      BoardPosition{1, 0},   BoardPosition{1, 1}};

  std::array<BoardPosition, 2> m_rook_positions;
  std::array<std::array<bool, 8>, 8> m_attash_mesh;
  std::vector<Move> m_enemy_move_buf;

  PlayerKind m_color;

  /// Checks whether all tiles between given positions (exluding both ends)
  /// in a single row are empty. 
  /// If given positions are not in the same row -- program fails on assertion.
  bool allEmptyInRowBetweenPositions(const Chessboard &board,
                                const BoardPosition &pos_1,
                                const BoardPosition &pos_2);

  /// Checks whether all tiles between given positions (*including* both ends)
  /// are not under attack of enemy piece.
  /// If given positions are not in the same row -- program fails on assertion.
  /// 
  /// Returns result calculated with respect to current state of `m_attack_mesh`.
  bool allNotAttackedInRowBetweenPositions(const BoardPosition &pos_1, const BoardPosition &pos_2);

  void updateAttackMesh(Chessboard &board, const BoardPosition &king_pos);
  void resetAttackMesh();
  
  /// Respective to current state of `m_attack_mesh`.
  bool isPositionAttacked(const BoardPosition &pos);
};

#endif // !__KING_MOVE_POLICY_HPP__
