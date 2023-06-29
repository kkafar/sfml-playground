#ifndef __PIECE_MOVE_POLICY_STORE_HPP__
#define __PIECE_MOVE_POLICY_STORE_HPP__

#include "Model/MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include <memory>

/// This object MUST NOT be moved or copied.
/// TODO: Delete copy / move ctors.
class PieceMovePolicyStore {
public:
  PieceMovePolicyStore();

  [[nodiscard]] inline std::shared_ptr<MovePolicy> pawnMovePolicy();
private:
  PawnMovePolicy m_pawn_move_policy;
};

#endif // !__PIECE_MOVE_POLICY_STORE_HPP__
