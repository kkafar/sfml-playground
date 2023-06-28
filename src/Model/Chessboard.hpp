#ifndef __CHESSBOARD_HPP__
#define __CHESSBOARD_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Piece.hpp"
#include "SFML/Config.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <optional>

class Chessboard {
public:
  Chessboard();

  /**
   * Returns optional of piece at given position.
   * Returned reference is *not* owning.
   */
  std::optional<std::reference_wrapper<Piece>> getPieceAt(BoardPosition pos);

  std::optional<Piece> removePieceFrom(BoardPosition pos);

  bool insertPieceAt(Piece &&piece, BoardPosition pos);

  bool movePiece(BoardPosition from_pos, BoardPosition to_pos);

  [[nodiscard]]
  bool isTileEmpty(BoardPosition pos);

private:
  // Array & pieces are owned by the Chessboard
  std::array<std::array<std::optional<Piece>, 8>, 8> m_board;
};

#endif // !__CHESSBOARD_HPP__
