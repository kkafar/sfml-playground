#ifndef __PAWN_MOVE_POLICY_HPP__
#define __PAWN_MOVE_POLICY_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"
#include "PieceKind.hpp"
#include <array>

class PawnMovePolicy : public MovePolicy {
public:  
  PawnMovePolicy(PlayerKind piece_color) : MovePolicy(PieceKind::Pawn), m_pawn_color(piece_color) {}

  /// Calculates all valid move-to positions for the figure from the given position
  /// and puts the result in provided vector. Make sure (or not) that the vector is empty
  /// before you pass it into this function.
  void allMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result) override;

private:
  PlayerKind m_pawn_color;
  constexpr static std::array<BoardPosition, 1> s_white_pawn_moves{
    {1, 0}
  };
  constexpr static std::array<BoardPosition, 1> s_black_pawn_moves{
    {-1, 0} 
  };

  void whitePawnMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result);
  void blackPawnMoves(const Piece &piece, Chessboard &board, std::vector<Move> &result);
  void pawnMovesFromOffsets(const Piece &piece, Chessboard &board, std::vector<Move> &result, const BoardPosition &potential_pos);
};

#endif // !__PAWN_MOVE_POLICY_HPP__
