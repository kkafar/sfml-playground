#include "Controller.hpp"
#include "Controller/PieceViewRegistry.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
#include "Model/PlayerKind.hpp"
#include "SFML/Config.hpp"
#include "SFML/System/Vector2.hpp"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <glog/logging.h>
#include <optional>

Controller::Controller(ChessboardView &&board_view, Chessboard &&board,
                       PieceViewRegistry &&pvr)
    : m_board_view(board_view), m_board(board), m_piece_view_registry(pvr) {
  BoardPosition current_position{0, 0};

  sf::Vector2u tile_dims = board_view.getTileSize();

  for (uint32_t i_row = 0; i_row < 8; ++i_row) {
    for (uint32_t i_col = 0; i_col < 8; ++i_col) {
      current_position.row = i_row;
      current_position.col = i_col;

      std::optional<std::reference_wrapper<Piece>> piece =
          m_board.getPieceAt(current_position);
      if (piece) {
        PieceView &piece_view =
            m_piece_view_registry.viewForTag(piece->get().tag())->get();
        sf::Vector2u piece_view_position =
            translateBoardPositionToWindowCoordinates(current_position);
        piece_view.setPosition(piece_view_position.x, piece_view_position.y);
        piece_view.setScale(static_cast<float>(tile_dims.x) /
                                piece_view.getTexture()->getSize().x,
                            static_cast<float>(tile_dims.y) /
                                piece_view.getTexture()->getSize().y);
      }
    }
  }
}

void Controller::focusPiece(Piece &piece) {
  if (m_focused_piece) {
    return;
  }

  m_focused_piece = std::make_optional(std::ref(piece));
  m_focused_piece_move_buf.clear();
 
  PieceView &view = m_piece_view_registry.viewForTag(piece.tag())->get();
  view.focus();

  piece.allMoves(m_board, m_focused_piece_move_buf);
  if (!m_focused_piece_move_buf.empty()) {
    m_board_view.tintPossibleMoves(piece, m_focused_piece_move_buf);
  }
}

void Controller::blurFocusedPiece() {
  if (!m_focused_piece) {
    return;
  }

  PieceView &view = m_piece_view_registry.viewForTag(m_focused_piece->get().tag())->get();
  view.blur();
  m_board_view.clearMoveTints(m_focused_piece_move_buf);
  m_focused_piece.reset();
}

std::optional<Move> Controller::positionIsInMoves(const BoardPosition &pos, const std::vector<Move> &moves) const {
  for (const Move &move : moves) {
    if (move.pos == pos) {
      return move;
    }
  }
  return std::nullopt;
}

void Controller::togglePlayer() {
  m_active_player = m_active_player == PlayerKind::White ? PlayerKind::Black : PlayerKind::White;
}

void Controller::performPlayerMove(Piece &piece, const Move &move) {
  movePiece(piece, move);
  if (move.kind == Move::Kind::Castle) {
    BoardPosition piece_pos = piece.position();
    BoardPosition rook_pos = BoardPosition { piece_pos.row, move.pos.col > piece_pos.col ? 7 : 0 };
    BoardPosition target_rook_pos = BoardPosition { piece_pos.row, move.pos.col > piece_pos.col ? piece_pos.col + 1 : piece_pos.col - 1 };

    Piece &rook = m_board.getPieceAt(rook_pos)->get();
    movePiece(rook, Move { target_rook_pos, Move::Kind::Normal });
  }
}

void Controller::movePiece(Piece &piece, const Move &move) {
  BoardPosition piece_pos = piece.position();

  m_board.movePiece(piece_pos, move.pos);

  sf::Vector2u view_pos = translateBoardPositionToWindowCoordinates(move.pos);
  m_piece_view_registry.viewForTag(piece.tag())->get().setPosition(view_pos.x, view_pos.y);
  
  blurFocusedPiece();
}

void Controller::removePiece(Piece &piece) {
  m_piece_view_registry.remove(piece.tag());
  m_board.removePieceFrom(piece.position());
}

void Controller::onMouseClicked(const sf::Event::MouseButtonEvent &event) {
  BoardPosition selected_pos =
      translateWindowCoordinatesToBoardPosition(event.x, event.y);
  std::optional<std::reference_wrapper<Piece>> selected_piece =
      m_board.getPieceAt(selected_pos);


  if (m_focused_piece) {
    if (selected_piece) {
      if (selected_piece->get() == m_focused_piece->get()) {
        blurFocusedPiece();
      } else if (selected_piece->get().color() == m_focused_piece->get().color()) {
        blurFocusedPiece();
        focusPiece(selected_piece->get());
      } else {
        std::optional<Move> move_opt = positionIsInMoves(selected_pos, m_focused_piece_move_buf);
        if (move_opt) {
          removePiece(selected_piece->get());
          performPlayerMove(m_focused_piece->get(), move_opt.value());
          togglePlayer();
        }
      }
    } else {
      std::optional<Move> move_opt = positionIsInMoves(selected_pos, m_focused_piece_move_buf);
      if (move_opt) {
        performPlayerMove(m_focused_piece->get(), move_opt.value());
        togglePlayer();
      } else {
        blurFocusedPiece();
      }
    }
  } else if (selected_piece) {
    if (selected_piece->get().color() == m_active_player) {
      focusPiece(selected_piece->get());
    }
  }
}

void Controller::onWindowResized(const sf::Event::SizeEvent &event) {
  m_board_view.resize(event.width, event.height);
}

BoardPosition
Controller::translateWindowCoordinatesToBoardPosition(int x, int y) const {
  int32_t row = std::clamp(
      static_cast<uint32_t>(y / m_board_view.getTileSize().y), 0u, 7u);
  int32_t col = std::clamp(
      static_cast<uint32_t>(x / m_board_view.getTileSize().x), 0u, 7u);
  return {row, col};
}

sf::Vector2u
Controller::translateBoardPositionToWindowCoordinates(BoardPosition pos) const {
  sf::Vector2u tile_size = m_board_view.getTileSize();
  return {pos.col * tile_size.x, pos.row * tile_size.y};
}
