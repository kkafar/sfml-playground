#include "Piece.hpp"
#include "Model/BishopMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/KingMovePolicy.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include "Model/QueenMovePolicy.hpp"
#include "Model/RookMovePolicy.hpp"
#include "PieceKind.hpp"
#include <memory>

std::unique_ptr<MovePolicy> movePolicyFactory(PieceKind piece, PlayerKind color) {
  switch (piece) {
    case PieceKind::Pawn:
      return std::make_unique<PawnMovePolicy>(color);
    case PieceKind::Rook:
      return std::make_unique<RookMovePolicy>();
    case PieceKind::Bishop:
      return std::make_unique<BishopMovePolicy>();
    case PieceKind::Queen:
      return std::make_unique<QueenMovePolicy>();
    case PieceKind::King:
      return std::make_unique<KingMovePolicy>();
    default:
      return std::make_unique<PawnMovePolicy>(color);
  }
}

Piece::Piece(const Piece::Color color, const PieceKind kind, const Tag tag)
    : m_color(color), m_kind(kind),
      m_tag(tag) {
  m_move_policy_delegate = movePolicyFactory(kind, color);
}

Piece::Piece(const Piece::Color color, const PieceKind kind,
             const BoardPosition pos, const Tag tag)
    : m_color(color), m_kind(kind), m_position(pos), m_tag(tag) {
  m_move_policy_delegate = movePolicyFactory(kind, color);
}
