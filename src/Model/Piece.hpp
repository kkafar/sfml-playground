#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/PlayerKind.hpp"
#include "PieceKind.hpp"
#include "SFML/Config.hpp"
#include <cstdint>
#include <memory>

class MovePolicy;

class Piece {
public:
  using Color = PlayerKind;
  using Tag = sf::Uint32;

  Piece(const Piece::Color color, const PieceKind kind,
        const std::shared_ptr<MovePolicy> mp_delegate, const Tag tag);

  Piece(const Piece::Color color, const PieceKind kind,
        const std::shared_ptr<MovePolicy> mp_delegate, const BoardPosition pos,
        const Tag tag);

  [[nodiscard]] inline const Tag tag() const noexcept { return m_tag; }

  inline void setPosition(const BoardPosition new_pos) { m_position = new_pos; }

private:
  BoardPosition m_position{0, 0};
  std::shared_ptr<MovePolicy> m_move_policy_delegate;
  Color m_color;
  PieceKind m_kind;
  Tag m_tag;
};

#endif // !__PIECE_HPP__
