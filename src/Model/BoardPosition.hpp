#ifndef __BOARD_POSITION_HPP__
#define __BOARD_POSITION_HPP__

#include <cstdint>
#include <ostream>

struct BoardPosition {
  int32_t row;
  int32_t col;

  friend std::ostream &operator<<(std::ostream &stream,
                                  const BoardPosition &pos) {
    stream << '(' << pos.row << ", " << pos.col << ')';
    return stream;
  }

  BoardPosition operator +(const BoardPosition &other) {
    return BoardPosition{row + other.row, col + other.col};
  }

  [[nodiscard]] inline bool operator ==(const BoardPosition &other) const noexcept {
    return row == other.row && col == other.col;
  }

  [[nodiscard]] inline bool operator !=(const BoardPosition &other) const noexcept {
    return row != other.row || col != other.col;
  }
};

#endif // !__BOARD_POSITION_HPP__
