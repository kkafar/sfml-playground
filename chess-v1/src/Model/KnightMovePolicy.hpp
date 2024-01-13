#ifndef __KNIGHT_MOVE_POLICY_HPP__
#define __KNIGHT_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
#include <array>

class KnightMovePolicy : public MovePolicy {
public:
  KnightMovePolicy() : MovePolicy(PieceKind::Knight) {}

  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;

private:
  constexpr static std::array<BoardPosition, 8> s_offsets {
    BoardPosition{-1, -2},
    BoardPosition{-2, -1},
    BoardPosition{-2, 1},
    BoardPosition{-1, 2},
    BoardPosition{1, 2},
    BoardPosition{2, 1},
    BoardPosition{2, -1},
    BoardPosition{1, -2}
  };
};

#endif // !__KNIGHT_MOVE_POLICY_HPP__
