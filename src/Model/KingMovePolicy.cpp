#include "KingMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
#include "Model/PlayerKind.hpp"
#include "SFML/Config.hpp"
#include "glog/logging.h"
#include <algorithm>
#include <cassert>
#include <cstdint>

KingMovePolicy::KingMovePolicy(const PlayerKind piece_color)
    : MovePolicy(PieceKind::King), m_color(piece_color) {
  int32_t starting_row;
  if (piece_color == PlayerKind::White) {
    starting_row = 0;
  } else {
    starting_row = 7;
  }
  m_rook_positions[0] = BoardPosition{starting_row, 0};
  m_rook_positions[1] = BoardPosition{starting_row, 7};
}

void KingMovePolicy::allMoves(const Piece &piece, Chessboard &board,
                              std::vector<Move> &result) {
  BoardPosition crt_pos;
  for (const BoardPosition &offset : KingMovePolicy::s_offsets) {
    crt_pos = piece.position() + offset;
    if (isPositionInChessboardBounds(crt_pos)) {
      if (board.isTileEmpty(crt_pos)) {
        result.push_back(Move{crt_pos, Move::Kind::Normal});
      } else if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        result.push_back(Move{crt_pos, Move::Kind::Attack});
      }
    }
  }

  if (!piece.wasMoved()) {
    LOG(INFO) << "Considering castling...";
    crt_pos = piece.position();
    std::optional<std::reference_wrapper<Piece>> rook_1_opt =
        board.getPieceAt(m_rook_positions[0]);
    std::optional<std::reference_wrapper<Piece>> rook_2_opt =
        board.getPieceAt(m_rook_positions[1]);

    if (rook_1_opt && rook_1_opt->get().color() == m_color &&
        !rook_1_opt->get().wasMoved() &&
        allEmptyInRowBetweenPositions(board, crt_pos, m_rook_positions[0])) {
      result.push_back(Move{BoardPosition{crt_pos.row, crt_pos.col - 2},
                            Move::Kind::Castle});
    }

    if (rook_2_opt && rook_1_opt->get().color() == m_color &&
        !rook_2_opt->get().wasMoved() &&
        allEmptyInRowBetweenPositions(board, crt_pos, m_rook_positions[1])) {
      result.push_back(Move{BoardPosition{crt_pos.row, crt_pos.col + 2},
                            Move::Kind::Castle});
    }
  } else {
    LOG(INFO) << "King was already moved can not castle";
  }
}

bool KingMovePolicy::allEmptyInRowBetweenPositions(const Chessboard &board,
                                                   const BoardPosition &pos_1,
                                                   const BoardPosition &pos_2) {
  assert(pos_1.row == pos_2.row);
  int32_t min_col = std::min(pos_1.col, pos_2.col);
  int32_t max_col = std::max(pos_1.col, pos_2.col);
  BoardPosition crt_pos{pos_1.row, min_col + 1};

  while (crt_pos.col < max_col && board.isTileEmpty(crt_pos)) {
    crt_pos.col++;
  }

  if (crt_pos.col == max_col) {
    return true;
  } else {
    return false;
  }
}
