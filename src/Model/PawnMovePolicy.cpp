#include "PawnMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"
#include <algorithm>
#include <glog/logging.h>


void PawnMovePolicy::allMoves(const Piece &piece, const Chessboard &board, std::vector<Move> &result) {
  LOG(INFO) << "PawnMovePolicy allMoves called";
  for (BoardPosition offset : PawnMovePolicy::s_possible_offsets) {
    BoardPosition potential_pos = piece.position() + offset;
    LOG(INFO) << "Considering position " << potential_pos;

    if (board.isTileEmpty(potential_pos)) {
      LOG(INFO) << "Pushing back Normal";
      result.push_back(Move { potential_pos, Move::Kind::Normal });
    } else {
      LOG(INFO) << "Pushing back Blocked";
      result.push_back(Move { potential_pos, Move::Kind::Blocked });
    }
  }
}
