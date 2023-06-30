#include "Controller.hpp"
#include "Controller/PieceViewRegistry.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
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

void Controller::blurPiece() {
  if (!m_focused_piece) {
    return;
  }

  PieceView &view = m_piece_view_registry.viewForTag(m_focused_piece->get().tag())->get();
  view.blur();
  m_focused_piece.reset();
  // TODO
  // m_board_view.removePossibleMovesTint
  
}

bool Controller::positionIsInMoves(const BoardPosition &pos, const std::vector<Move> &moves) const {
  for (const Move &move : moves) {
    if (move.pos == pos) {
      return true;
    }
  }
  return false;
}

void Controller::movePiece(Piece &piece, const BoardPosition &to_pos) {
  m_board.movePiece(piece.position(), to_pos);

  sf::Vector2u view_pos = translateBoardPositionToWindowCoordinates(to_pos);
  m_piece_view_registry.viewForTag(piece.tag())->get().setPosition(view_pos.x, view_pos.y);
  blurPiece();
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
        blurPiece();
      } else if (selected_piece->get().color() == m_focused_piece->get().color()) {
        blurPiece();
        focusPiece(selected_piece->get());
      } else {
        if (positionIsInMoves(selected_pos, m_focused_piece_move_buf)) {
          removePiece(selected_piece->get());
          movePiece(m_focused_piece->get(), selected_pos);
        }
      }
    } else {
      if (positionIsInMoves(selected_pos, m_focused_piece_move_buf)) {
        movePiece(m_focused_piece->get(), selected_pos);
      } else {
        blurPiece();
      }
    }
  } else if (selected_piece) {
    focusPiece(selected_piece->get());
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
