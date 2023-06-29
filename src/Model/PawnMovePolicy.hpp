#ifndef __PAWN_MOVE_POLICY_HPP__
#define __PAWN_MOVE_POLICY_HPP__

#include "Model/MovePolicy.hpp"
#include "PieceKind.hpp"

class PawnMovePolicy : public MovePolicy {
public:  
  PawnMovePolicy() : MovePolicy(PieceKind::Pawn) {}

  /// Calculates all valid move-to positions for the figure from the given position
  /// and puts the result in provided vector. Make sure (or not) that the vector is empty
  /// before you pass it into this function.
  void availableMoves(const Piece &piece, const Chessboard &board, std::vector<Move> &result) override;

private:
};

#endif // !__PAWN_MOVE_POLICY_HPP__