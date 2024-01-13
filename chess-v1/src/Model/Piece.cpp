#include "Piece.hpp"
#include "Model/BishopMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/KingMovePolicy.hpp"
#include "Model/KnightMovePolicy.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include "Model/QueenMovePolicy.hpp"
#include "Model/RookMovePolicy.hpp"
#include "PieceKind.hpp"
#include "glog/logging.h"
#include <memory>

std::unique_ptr<MovePolicy> Piece::movePolicyFactory(PieceKind piece, PlayerKind color) {
  switch (piece) {
    case PieceKind::Pawn:
      return std::make_unique<PawnMovePolicy>(color);
    case PieceKind::Rook:
      return std::make_unique<RookMovePolicy>();
    case PieceKind::Bishop:
      return std::make_unique<BishopMovePolicy>();
    case PieceKind::Queen:
      LOG(INFO) << "Returning delegate for queen";
      return std::make_unique<QueenMovePolicy>();
    case PieceKind::King:
      return std::make_unique<KingMovePolicy>(color);
    case PieceKind::Knight:
      return std::make_unique<KnightMovePolicy>();
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
