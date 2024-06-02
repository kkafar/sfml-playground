#include "Piece.h"
#include <core/Constants.h>

Piece::Piece(PieceColor color, PieceKind kind) noexcept:
        color_(color),
        kind_(kind),
        tag_{TAG_UNSET} {}

inline PieceColor Piece::GetColor() const noexcept {
    return this->color_;
}

inline PieceKind Piece::GetKind() const noexcept {
    return this->kind_;
}

inline Tag Piece::GetTag() const noexcept {
    return this->tag_;
}

inline void Piece::SetTag(Tag tag) noexcept {
    this->tag_ = tag;
}
