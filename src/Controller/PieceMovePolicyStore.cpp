#include "PieceMovePolicyStore.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include <memory>

PieceMovePolicyStore::PieceMovePolicyStore() : m_pawn_move_policy(PlayerKind::White) {
  
}

std::shared_ptr<MovePolicy> PieceMovePolicyStore::pawnMovePolicy() {
  return std::shared_ptr<MovePolicy>(&m_pawn_move_policy);
}
