#include "Chessboard.hpp"
#include "Model/BoardPosition.hpp"
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
    return std::make_optional<std::reference_wrapper<Piece>>(std::ref(piece_opt.value()));
  } else {
    return std::nullopt;
  }
}

std::optional<Piece> Chessboard::removePieceFrom(BoardPosition pos) {
  std::optional<Piece> return_value = m_board[pos.row][pos.col];
  m_board[pos.row][pos.col] = std::nullopt;
  return return_value;
}

bool Chessboard::insertPieceAt(Piece &&piece, BoardPosition pos) {
  if (m_board[pos.row][pos.col]) {
    return false;
  }
  piece.setPosition(pos);
  m_board[pos.row][pos.col] = std::make_optional<Piece>(piece);
  return true;
}

inline bool Chessboard::isTileEmpty(BoardPosition pos) const {
  return m_board[pos.row][pos.col].has_value();
}

bool Chessboard::movePiece(BoardPosition from_pos, BoardPosition to_pos) {
  if (!isTileEmpty(to_pos)) {
    return false;
  }

  std::optional<Piece> piece = getPieceAt(from_pos);

  if (!piece) {
    return false;
  }

  return insertPieceAt(std::move(piece.value()), to_pos);
}
