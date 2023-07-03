#include "Chessboard.hpp"
#include "Model/BoardPosition.hpp"
#include "glog/logging.h"
#include <cstdint>
#include <functional>
#include <math.h>
#include <optional>

Chessboard::Chessboard() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      m_board[i][j] = std::nullopt;
    }
  }
}
  
std::optional<std::reference_wrapper<Piece>> Chessboard::getPieceAt(BoardPosition pos) {
  std::optional<Piece> &piece_opt = m_board[pos.row][pos.col];
  if (piece_opt) {
    LOG(INFO) << "Piece found at " << pos;
    return std::make_optional<std::reference_wrapper<Piece>>(std::ref(piece_opt.value()));
  } else {
    return std::nullopt;
  }
}

std::optional<Piece> Chessboard::removePieceFrom(BoardPosition pos) {
  // std::optional<Piece> return_value = std::move(m_board[pos.row][pos.col]);
  std::optional<Piece> return_value = std::move(m_board[pos.row][pos.col]);
  m_board[pos.row][pos.col] = std::nullopt;
  return return_value;
}

bool Chessboard::insertPieceAt(Piece &&piece, BoardPosition pos) {
  if (m_board[pos.row][pos.col]) {
    return false;
  }
  piece.setPosition(pos);
  m_board[pos.row][pos.col] = std::make_optional<Piece>(std::move(piece));
  return true;
}

bool Chessboard::isTileEmpty(BoardPosition pos) const {
  // LOG(INFO) << "Chessboard::isTileEmpty for " << pos << " returns " << !m_board[pos.row][pos.col].has_value();
  return !m_board[pos.row][pos.col].has_value();
}

bool Chessboard::movePiece(BoardPosition from_pos, BoardPosition to_pos) {
  std::optional<Piece> piece = removePieceFrom(from_pos);

  if (!piece) {
    LOG(ERROR) << "Attempted to remove piece from empty position";
    return false;
  }
  piece.value().markAsMoved();

  return insertPieceAt(std::move(piece.value()), to_pos);
}
