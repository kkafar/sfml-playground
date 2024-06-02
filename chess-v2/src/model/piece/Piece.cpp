#include "Piece.h"
#include <core/Constants.h>
#include <glog/logging.h>
#include <iomanip>

PieceUtil::ColorMap PieceUtil::kColorMapping = {
        {"white", Piece::Color::kWhite},
        {"black", Piece::Color::kBlack},
};

PieceUtil::PieceMap PieceUtil::kPieceMapping = {
        {"pawn", Piece::Kind::kPawn},
        {"bishop", Piece::Kind::kBishop},
        {"king", Piece::Kind::kKing},
        {"knight", Piece::Kind::kKnight},
        {"queen", Piece::Kind::kQueen},
        {"rook", Piece::Kind::kRook},
};

Piece::Piece(Piece::Color color, Piece::Kind kind) noexcept:
        color_(color),
        kind_(kind),
        tag_{TAG_UNSET} {}

inline Piece::Color Piece::GetColor() const noexcept {
    return this->color_;
}

inline Piece::Kind Piece::GetKind() const noexcept {
    return this->kind_;
}

inline Tag Piece::GetTag() const noexcept {
    return this->tag_;
}

inline void Piece::SetTag(Tag tag) noexcept {
    this->tag_ = tag;
}

Piece::Kind PieceUtil::KindFromString(const std::string &kind_str) {
    frozen::string key{kind_str.data(), kind_str.size()};
    return PieceUtil::kPieceMapping.at(key);
}

Piece::Color PieceUtil::ColorFromString(const std::string &color_str) {
    // Yeah, I do not know how painful this conversion is, but this is the price I'm paying for
    // experimenting with this library and using it in non-constexpr context.
    frozen::string key{color_str.data(), color_str.size()};
    return PieceUtil::kColorMapping.at(key);
}
