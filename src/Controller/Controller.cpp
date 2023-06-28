#include "Controller.hpp"

Controller::Controller(ChessboardView &&board_view, Chessboard &&board)
    : m_board_view(board_view), m_board(board) {}
