#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "Model/MovePolicy.hpp"
#include "Model/PlayerKind.hpp"

class Piece {
public: 
  using Color = PlayerKind;

  Piece(Piece::Color color, MovePolicy move_policy);

private:
  MovePolicy m_move_policy;
  Color m_color;
};

#endif // !__PIECE_HPP__
