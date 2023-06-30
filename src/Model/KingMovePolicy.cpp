#include "KingMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"

void KingMovePolicy::allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
  BoardPosition crt_pos;
  for (const BoardPosition &offset : KingMovePolicy::s_offsets) {
    crt_pos = piece.position() + offset;
    if (isPositionInChessboardBounds(crt_pos)) {
      if (board.isTileEmpty(crt_pos)) {
        result.push_back(Move { crt_pos, Move::Kind::Normal });
      } else if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
    }
  }
}
