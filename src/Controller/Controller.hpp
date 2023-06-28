#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "View/ChessboardView.hpp"

class Controller {
public:
  Controller(ChessboardView &&board_view, Chessboard &&board);

  void onMouseClicked(const sf::Event::MouseButtonEvent &event);

private:
  ChessboardView m_board_view;
  Chessboard m_board;

  BoardPosition translateWindowCoordinatesToBoardPosition(int x, int y) const;
  sf::Vector2u translateBoardPositionToWindowCoordinates(BoardPosition pos) const;
};

#endif // !__CONTROLLER_HPP__
