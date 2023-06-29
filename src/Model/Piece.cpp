#include "Piece.hpp"
#include "PieceKind.hpp"

Piece::Piece(const Piece::Color color, const PieceKind kind, const MovePolicy move_policy, const Tag tag)
    : m_color(color), m_kind(kind), m_move_policy(move_policy), m_tag(tag) {}
