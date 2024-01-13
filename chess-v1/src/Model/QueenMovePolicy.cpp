#include "QueenMovePolicy.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"
#include "glog/logging.h"

void QueenMovePolicy::allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
  LOG(INFO) << "Calculating moves for Queen";
  m_bishop_delegate.allMoves(piece, board, result);
  m_rook_delegate.allMoves(piece, board, result);
}
