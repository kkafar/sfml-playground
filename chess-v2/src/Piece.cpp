#include "Piece.h"

namespace chess {

Piece::Piece(PieceColor color, PieceKind kind) noexcept : color_(color), kind_(kind) {

}

PieceColor Piece::GetColor() const noexcept {
    return this->color_;
}

PieceKind Piece::GetKind() const noexcept {
    return this->kind_;
}

}


