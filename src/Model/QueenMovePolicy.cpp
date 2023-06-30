#include "QueenMovePolicy.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"

void QueenMovePolicy::allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
  m_bishop_delegate.allMoves(piece, board, result);
  m_rook_delegate.allMoves(piece, board, result);
}
