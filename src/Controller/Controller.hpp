#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "Controller/PieceViewRegistry.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "View/ChessboardView.hpp"
#include <functional>
#include <optional>

class Controller {
public:
  Controller(ChessboardView &&board_view, Chessboard &&board, PieceViewRegistry &&pvr);

  void onMouseClicked(const sf::Event::MouseButtonEvent &event);
  void onWindowResized(const sf::Event::SizeEvent &event);

  inline const ChessboardView &chessboardView() { return m_board_view; }
  inline const PieceViewRegistry &pieceViews() { return m_piece_view_registry; }

private:
  ChessboardView m_board_view;
  Chessboard m_board;
  PieceViewRegistry m_piece_view_registry;
  std::optional<std::reference_wrapper<Piece>> m_focused_piece{std::nullopt};


  BoardPosition translateWindowCoordinatesToBoardPosition(int x, int y) const;
  sf::Vector2u translateBoardPositionToWindowCoordinates(BoardPosition pos) const;
};

#endif // !__CONTROLLER_HPP__
