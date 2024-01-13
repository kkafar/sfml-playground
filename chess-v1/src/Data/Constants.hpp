#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include "Model/PieceKind.hpp"
#include <array>

class Constant {
public: 
  constexpr static std::array<PieceKind, 8> piece_order = {
      PieceKind::Rook, PieceKind::Knight, PieceKind::Bishop, PieceKind::Queen,
      PieceKind::King, PieceKind::Bishop, PieceKind::Knight, PieceKind::Rook
  };
};

#endif // !__CONSTANTS_HPP__
