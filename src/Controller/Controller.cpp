#include "Controller.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Piece.hpp"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <glog/logging.h>

Controller::Controller(ChessboardView &&board_view, Chessboard &&board)
    : m_board_view(board_view), m_board(board) {}

void Controller::onMouseClicked(const sf::Event::MouseButtonEvent &event) {
  BoardPosition selected_pos = translateWindowCoordinatesToBoardPosition(event.x, event.y);
  std::optional<std::reference_wrapper<Piece>> selected_piece = m_board.getPieceAt(selected_pos);
  if (selected_piece) {
    LOG(INFO) << "Player selected piece at position" << selected_pos;
  }
}

BoardPosition Controller::translateWindowCoordinatesToBoardPosition(int x, int y) {
  uint32_t row = std::clamp(static_cast<uint32_t>(y / m_board_view.getTileSize().y), 0u, 7u);
  uint32_t col = std::clamp(static_cast<uint32_t>(x / m_board_view.getTileSize().x), 0u, 7u);
  return {row, col};
}
