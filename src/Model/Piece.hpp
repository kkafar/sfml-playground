#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Move.hpp"
#include "Model/PlayerKind.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/QueenMovePolicy.hpp"
#include "PieceKind.hpp"
#include "SFML/Config.hpp"
#include <cstdint>
#include <memory>
#include <array>
#include <glog/logging.h>

class Chessboard;

class Piece {
public:
  using Color = PlayerKind;
  using Kind = PieceKind;
  using Tag = sf::Uint32;

  Piece(const Piece &) = delete;
  Piece(Piece &&) = default;
  Piece &operator=(const Piece &) = delete;
  Piece &operator=(Piece &&) = default;

  Piece(const Piece::Color color, const PieceKind kind, const Tag tag);

  Piece(const Piece::Color color, const PieceKind kind, const BoardPosition pos, const Tag tag);

  [[nodiscard]] inline const Tag tag() const noexcept { return m_tag; }

  [[nodiscard]] inline Color color() const noexcept { return m_color; }

  [[nodiscard]] inline PieceKind kind() const noexcept { return m_kind; }

  [[nodiscard]] inline BoardPosition position() const noexcept { return m_position; }

  void setKind(Piece::Kind kind) {
    LOG(INFO) << "Changing from pawn to queen for piece at " << this;
    m_kind = kind;
    m_move_policy_delegate = movePolicyFactory(m_kind, m_color);
  }

  void allMoves(Chessboard &board, std::vector<Move> &result) {
    LOG(INFO) << "Calculating moves for piece at " << this;
    m_move_policy_delegate->allMoves(*this, board, result);
    LOG(INFO) << "Moves calculated: " << result.size();
  }
  
  void attackMoves(Chessboard &board, std::vector<Move> &result) {
    m_move_policy_delegate->attackMoves(*this, board, result);
  }

  inline void setPosition(const BoardPosition new_pos) noexcept { m_position = new_pos; }

  void markAsMoved() noexcept { m_has_moved = true; }

  [[nodiscard]] bool wasMoved() const noexcept { return m_has_moved; }

  [[nodiscard]] inline bool operator ==(const Piece &other) const noexcept {
    return this->m_tag == other.m_tag; 
  }

  [[nodiscard]] inline bool operator !=(const Piece &other) const noexcept {
    return this->m_tag != other.m_tag;
  }

private:
  BoardPosition m_position{0, 0};
  bool m_has_moved{false};
  std::unique_ptr<MovePolicy> m_move_policy_delegate;
  Color m_color;
  PieceKind m_kind;
  Tag m_tag;


  static std::unique_ptr<MovePolicy> movePolicyFactory(PieceKind piece, PlayerKind color);
};

#endif // !__PIECE_HPP__
