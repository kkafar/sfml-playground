#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include "PieceKind.hpp"
#include <cstdint>

class Piece {
public:
  using Color = PlayerKind;
  using Tag = int32_t;

  Piece(const Piece::Color color, const PieceKind kind, const MovePolicy move_policy, const Tag tag);

  [[nodiscard]] inline Tag tag() { return m_tag; }

private:
  MovePolicy m_move_policy;
  Color m_color;
  PieceKind m_kind;
  Tag m_tag;
};

#endif // !__PIECE_HPP__
