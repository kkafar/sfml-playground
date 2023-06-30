#include "PawnMovePolicy.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
#include <algorithm>
#include <glog/logging.h>

void PawnMovePolicy::allMoves(const Piece &piece, Chessboard &board,
                              std::vector<Move> &result) {
  LOG(INFO) << "Calculating moves for Pawn";
  if (piece.color() == Piece::Color::White) {
    whitePawnMoves(piece, board, result);
  } else {
    blackPawnMoves(piece, board, result);
  }
}

void PawnMovePolicy::whitePawnMoves(const Piece &piece, Chessboard &board,
                                    std::vector<Move> &result) {
  LOG(INFO) << "Calculating moves for WhitePawn";
  for (BoardPosition offset : PawnMovePolicy::s_white_pawn_moves) {
    BoardPosition potential_pos = piece.position() + offset;
    pawnMovesFromOffsets(piece, board, result, potential_pos);
  }
}

void PawnMovePolicy::blackPawnMoves(const Piece &piece, Chessboard &board,
                                    std::vector<Move> &result) {
  LOG(INFO) << "Calculating moves for BlackPawn";
  for (BoardPosition offset : PawnMovePolicy::s_black_pawn_moves) {
    BoardPosition potential_pos = piece.position() + offset;
    pawnMovesFromOffsets(piece, board, result, potential_pos);
  }
}

void PawnMovePolicy::pawnMovesFromOffsets(const Piece &piece, Chessboard &board,
                                          std::vector<Move> &result,
                                          const BoardPosition &potential_pos) {
  // LOG(INFO) << "Considering position: " << potential_pos;

  if (isPositionInChessboardBounds(potential_pos)) {
    // LOG(INFO) << "Position lies on the board";
    if (board.isTileEmpty(potential_pos)) {
      // LOG(INFO) << "Position is empty";
      result.push_back(Move{potential_pos, Move::Kind::Normal});
    } else {
      LOG_IF(ERROR, !board.getPieceAt(potential_pos)) << "Board returned nullopt instead of piece";

      const Piece &piece_at_target_pos = board.getPieceAt(potential_pos)->get();
      if (piece_at_target_pos.color() == piece.color()) {
        // LOG(INFO) << "Position is occupied by the same color piece";
        result.push_back(Move{potential_pos, Move::Kind::Blocked});
      } else {
        // LOG(INFO) << "Position is occupied by different color piece";
        result.push_back(Move{potential_pos, Move::Kind::Attack});
      }
    }
  }
}
