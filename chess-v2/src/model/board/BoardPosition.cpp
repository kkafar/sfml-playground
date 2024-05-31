//
// Created by kkafara on 1/13/24.
//

#include "BoardPosition.h"

std::ostream &chess::operator<<(std::ostream &stream, const chess::BoardPosition &pos) {
    stream << "{" << pos.row << ", " << pos.col << "}";
    return stream;
}

namespace chess {

inline BoardPosition BoardPosition::operator+(const BoardPosition &other) const noexcept {
    return BoardPosition{this->row + other.row, this->col + other.col};
}

inline bool BoardPosition::operator==(const BoardPosition &other) const noexcept {
    return row == other.row && col == other.col;
}

inline bool BoardPosition::operator!=(const BoardPosition &other) const noexcept {
    return row != other.row || col != other.col;
}

BoardPosition &BoardPosition::operator+=(const BoardPosition &other) noexcept {
    row += other.row;
    col += other.col;
    return *this;
}

BoardPosition &BoardPosition::operator-=(const BoardPosition &other) noexcept {
    row -= other.row;
    col -= other.col;
    return *this;
}

}

