#ifndef __CHESSBOARD_HPP__
#define __CHESSBOARD_HPP__

#include "PieceKind.hpp"
#include <array>
#include <optional>
class Chessboard {
public: 
  Chessboard();

private:
  std::array<std::array<std::optional<PieceKind>, 8>, 8> m_board;

};

#endif // !__CHESSBOARD_HPP__
