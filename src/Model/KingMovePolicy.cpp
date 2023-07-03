#include "KingMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Move.hpp"
#include "Model/Piece.hpp"
#include "Model/PlayerKind.hpp"
#include "SFML/Config.hpp"
#include "glog/logging.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <optional>

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
  updateAttackMesh(board, piece.position());
  BoardPosition crt_pos;
  for (const BoardPosition &offset : KingMovePolicy::s_offsets) {
    crt_pos = piece.position() + offset;
    if (isPositionInChessboardBounds(crt_pos) && !isPositionAttacked(crt_pos)) {
      if (board.isTileEmpty(crt_pos)) {
        LOG(INFO) << crt_pos << " empty and not under attack";
        result.push_back(Move{crt_pos, Move::Kind::Normal});
      } else if (board.getPieceAt(crt_pos)->get().color() != piece.color()) {
        LOG(INFO) << crt_pos << " occupied by enemy but not under attack";
        result.push_back(Move{crt_pos, Move::Kind::Attack});
      }
    }
  }

  // Castling
  if (!piece.wasMoved()) {
    LOG(INFO) << "Considering castling...";
    crt_pos = piece.position();
    std::optional<std::reference_wrapper<Piece>> rook_1_opt =
        board.getPieceAt(m_rook_positions[0]);
    std::optional<std::reference_wrapper<Piece>> rook_2_opt =
        board.getPieceAt(m_rook_positions[1]);

    BoardPosition target_king_pos = BoardPosition{crt_pos.row, crt_pos.col - 2};

    if (rook_1_opt && rook_1_opt->get().color() == m_color &&
        !rook_1_opt->get().wasMoved() &&
        allEmptyInRowBetweenPositions(board, crt_pos, m_rook_positions[0]) &&
        allNotAttackedInRowBetweenPositions(crt_pos, target_king_pos)) {
      result.push_back(Move{target_king_pos,
                            Move::Kind::Castle});
    }

    target_king_pos = BoardPosition{crt_pos.row, crt_pos.col + 2};
    if (rook_2_opt && rook_1_opt->get().color() == m_color &&
        !rook_2_opt->get().wasMoved() &&
        allEmptyInRowBetweenPositions(board, crt_pos, m_rook_positions[1]) &&
        allNotAttackedInRowBetweenPositions(crt_pos, target_king_pos)) {
      result.push_back(Move{target_king_pos,
                            Move::Kind::Castle});
    }
  } else {
    LOG(INFO) << "King was already moved can not castle";
  }
}

bool KingMovePolicy::allNotAttackedInRowBetweenPositions(
    const BoardPosition &pos_1, const BoardPosition &pos_2) {
  assert(pos_1.row == pos_2.row);
  int32_t min_col = std::min(pos_1.col, pos_2.col);
  int32_t max_col = std::max(pos_1.col, pos_2.col);
  BoardPosition crt_pos{pos_1.row, min_col};
  while (crt_pos.col <= max_col && !isPositionAttacked(crt_pos)) {
    crt_pos.col++;
  }
  if (crt_pos.col > max_col) {
    return true;
  } else {
    return false;
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

bool KingMovePolicy::isPositionAttacked(const BoardPosition &pos) {
  return m_attash_mesh[pos.row][pos.col];
}

void KingMovePolicy::resetAttackMesh() {
  for (int32_t i = 0; i < 8; ++i) {
    for (int32_t j = 0; j < 8; ++j) {
      m_attash_mesh[i][j] = false;
    }
  }
}

void KingMovePolicy::updateAttackMesh(Chessboard &board, const BoardPosition &king_pos) {
  resetAttackMesh();

  for (int32_t i = 0; i < 8; ++i) {
    for (int32_t j = 0; j < 8; ++j) {
      BoardPosition pos = BoardPosition{i, j};
      if (pos == king_pos) {
        continue;
      }
      std::optional<std::reference_wrapper<Piece>> piece_opt =
          board.getPieceAt(pos);
      if (piece_opt.has_value()) {
        Piece &piece = piece_opt->get();
        // FIXME: I'm not taking into consideration enemy king,
        // as doing so leads to infinite loop (updateAttackMesh is called for enemy king,
        // and then for this king, etc.).
        if (piece.color() != m_color && piece.kind() != Piece::Kind::King) {
          m_enemy_move_buf.clear();
          LOG(INFO) << "Calculating attack moves for piece at " << piece.position();
          piece.attackMoves(board, m_enemy_move_buf);
          for (const Move &move : m_enemy_move_buf) {
            m_attash_mesh[move.pos.row][move.pos.col] = true;
          }
        }
      }
    }
  }
}
