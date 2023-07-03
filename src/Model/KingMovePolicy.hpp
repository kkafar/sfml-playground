#ifndef __KING_MOVE_POLICY_HPP__
#define __KING_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
#include "SFML/Config.hpp"
#include <array>

class KingMovePolicy : public MovePolicy {
public:
  KingMovePolicy(const sf::Int32 starting_row);

  void allMoves(const Piece &piece, Chessboard &board,
                std::vector<Move> &result) override;

private:
  constexpr static std::array<BoardPosition, 8> s_offsets{
      BoardPosition{-1, -1}, BoardPosition{-1, 0}, BoardPosition{-1, 1},
      BoardPosition{0, -1},  BoardPosition{0, 1},  BoardPosition{1, -1},
      BoardPosition{1, 0},   BoardPosition{1, 1}};

  std::array<BoardPosition, 2> m_rook_positions;

  bool allEmptyInRowBetweenPositions(const Chessboard &board,
                                const BoardPosition &pos_1,
                                const BoardPosition &pos_2);
};

#endif // !__KING_MOVE_POLICY_HPP__
