#ifndef __MOVE_HPP__
#define __MOVE_HPP__

#include "Model/BoardPosition.hpp"

struct Move {
  enum class Kind {
    Normal,
    Attack,
    Castle,
    Blocked,
    Invalid,
  };

  BoardPosition pos;  
  Kind kind;
};

#endif // ! __MOVE_HPP__
