#include "Piece.hpp"

Piece::Piece(Piece::Color color, MovePolicy move_policy)
    : m_color(color), m_move_policy(move_policy) {}
