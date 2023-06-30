#include "BishopMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Piece.hpp"
#include "Model/Chessboard.hpp"


void BishopMovePolicy::allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) {
  BoardPosition crt_pos = piece.position();

  // Left-up
  crt_pos.row -= 1;
  crt_pos.col -= 1;
  while (crt_pos.row >= 0 && crt_pos.col >= 0) {
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
    crt_pos.row -= 1;
    crt_pos.col -= 1;
  }

  // Right-up
  crt_pos = piece.position();
  crt_pos.row -= 1;
  crt_pos.col += 1;
  while (crt_pos.row >= 0 && crt_pos.col < 8) {
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
    crt_pos.row -= 1;
    crt_pos.col += 1;
  }
  
  // Left-down
  crt_pos = piece.position();
  crt_pos.row += 1;
  crt_pos.col -= 1;
  while (crt_pos.row < 8 && crt_pos.col >= 0) {
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
    crt_pos.row += 1;
    crt_pos.col -= 1;
  }
  
  // Right-down
  crt_pos = piece.position();
  crt_pos.row += 1;
  crt_pos.col += 1;
  while (crt_pos.row < 8 && crt_pos.col < 8) {
    if (board.isTileEmpty(crt_pos)) {
      result.push_back(Move { crt_pos, Move::Kind::Normal });
    } else {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
      break;
    }
    crt_pos.row += 1;
    crt_pos.col += 1;
  }
}
