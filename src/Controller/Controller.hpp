#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "Model/Chessboard.hpp"
#include "View/ChessboardView.hpp"

class Controller {
public:
  Controller(ChessboardView &&board_view, Chessboard &&board);

private:
  ChessboardView m_board_view;
  Chessboard m_board;
};

#endif // !__CONTROLLER_HPP__
