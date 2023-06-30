#include "RookMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"

void RookMovePolicy::allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
  BoardPosition crt_pos = piece.position();

  // Moves to the left
  for (int i = crt_pos.col - 1; i >= 0; --i) {
    crt_pos.col = i;
    // LOG(INFO) << "RookMovePolicy::allMoves looking at pos " << crt_pos;
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
  }

  // Moves to the right
  crt_pos = piece.position();
  for (int i = crt_pos.col + 1; i < 8; ++i) {
    crt_pos.col = i;
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
  }

  // Moves up
  crt_pos = piece.position();
  for (int i = crt_pos.row + 1; i < 8; ++i) {
    crt_pos.row = i;
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
  }
  
  // Moves down
  crt_pos = piece.position();
  for (int i = crt_pos.row - 1; i >= 0; --i) {
    crt_pos.row = i;
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
  }
}
