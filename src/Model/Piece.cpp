#include "Piece.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"
#include <memory>

Piece::Piece(const Piece::Color color, const PieceKind kind,
             const std::shared_ptr<MovePolicy> mp_delegate, const Tag tag)
    : m_color(color), m_kind(kind), m_move_policy_delegate(mp_delegate),
      m_tag(tag) {}

Piece::Piece(const Piece::Color color, const PieceKind kind,
             const std::shared_ptr<MovePolicy> mp_delegate,
             const BoardPosition pos, const Tag tag)
    : m_color(color), m_kind(kind), m_move_policy_delegate(mp_delegate),
      m_position(pos), m_tag(tag) {}
