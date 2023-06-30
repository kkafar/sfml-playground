#ifndef __KING_MOVE_POLICY_HPP__
#define __KING_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
#include <array>

class KingMovePolicy : public MovePolicy {
public:
  KingMovePolicy() : MovePolicy(PieceKind::King) {}

  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;

private:
  constexpr static std::array<BoardPosition, 8> s_offsets {
    BoardPosition{-1, -1}, 
    BoardPosition{-1, 0},
    BoardPosition{-1, 1},
    BoardPosition{0, -1},
    BoardPosition{0, 1},
    BoardPosition{1, -1},
    BoardPosition{1, 0},
    BoardPosition{1, 1} 
  };
};

#endif // !__KING_MOVE_POLICY_HPP__
