#include "PawnMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
#include "Model/PlayerKind.hpp"
#include <algorithm>
#include <glog/logging.h>

PawnMovePolicy::PawnMovePolicy(PlayerKind piece_color) : MovePolicy(PieceKind::Pawn), m_pawn_color(piece_color) {
  if (m_pawn_color == PlayerKind::Black) {
    m_normal_move_offset = BoardPosition{-1, 0};
    m_attack_move_offsets[0] = BoardPosition{-1, -1};
    m_attack_move_offsets[1] = BoardPosition{-1, 1};
    m_initial_row = 6;
  } else {
    m_normal_move_offset = BoardPosition{1, 0};
    m_attack_move_offsets[0] = BoardPosition{1, -1};
    m_attack_move_offsets[1] = BoardPosition{1, 1};
    m_initial_row = 1;
  }
}

void PawnMovePolicy::allMoves(const Piece &piece, Chessboard &board,
                              std::vector<Move> &result) {
  BoardPosition crt_pos = piece.position() + m_normal_move_offset;
  if (isPositionInChessboardBounds(crt_pos) && board.isTileEmpty(crt_pos)) {
    result.push_back(Move { crt_pos, Move::Kind::Normal });
  }

  crt_pos += m_normal_move_offset;
  if (isInInitialRow(piece) && isPositionInChessboardBounds(crt_pos) && board.isTileEmpty(crt_pos)) {
    result.push_back(Move { crt_pos, Move::Kind::Normal });
  }

  for (const BoardPosition &offset : m_attack_move_offsets) {
    crt_pos = piece.position() + offset;
    if (isPositionInChessboardBounds(crt_pos) && !board.isTileEmpty(crt_pos)) {
      if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move { crt_pos, Move::Kind::Attack });
      }
    }
  }
}

bool PawnMovePolicy::isInInitialRow(const Piece &piece) {
  return piece.position().row == m_initial_row;
}
