#include "Piece.h"

namespace chess::model::piece {

    Piece::Piece(PieceColor color, PieceKind kind) noexcept: color_(color), kind_(kind) {

    }

    inline PieceColor Piece::GetColor() const noexcept {
        return this->color_;
    }

    inline PieceKind Piece::GetKind() const noexcept {
        return this->kind_;
    }

}


