#include "PawnMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"
#include <algorithm>


void PawnMovePolicy::allMoves(const Piece &piece, const Chessboard &board, std::vector<Move> &result) {
  for (BoardPosition offset : PawnMovePolicy::s_possible_offsets) {
    BoardPosition potential_pos = piece.position() + offset;

    if (board.isTileEmpty(potential_pos)) {
      result.push_back(Move { potential_pos, Move::Kind::Normal });
    } else {
      result.push_back(Move { potential_pos, Move::Kind::Blocked });
    }
  }
}
