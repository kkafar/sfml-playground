#ifndef CHESS_V2_PIECE_H
#define CHESS_V2_PIECE_H

#include <core/CommonTypes.h>
#include <string>
#include <frozen/unordered_map.h>
#include <frozen/string.h>

class Piece {
public:
    enum class Color {
        kWhite = 0,
        kBlack,
    };

    enum class Kind {
        kPawn = 0,
        kBishop,
        kKing,
        kKnight,
        kQueen,
        kRook,
    };

    Piece(const Piece &) = delete;

    Piece(Piece &&) = default;

    Piece &operator=(const Piece &) = delete;

    Piece &operator=(Piece &&) = default;

    explicit Piece(Piece::Color color, Piece::Kind kind) noexcept;

    [[nodiscard]] Piece::Color GetColor() const noexcept;

    [[nodiscard]] Piece::Kind GetKind() const noexcept;

    void SetTag(Tag tag) noexcept;

    [[nodiscard]] Tag GetTag() const noexcept;

private:
    Piece::Color color_;
    Piece::Kind kind_;
    Tag tag_;
};


class PieceUtil final {
public:
    // Q: Why not std::unordered_map?
    // A: Dunno, just wanted to try it out.
    using ColorMap = frozen::unordered_map<frozen::string, Piece::Color, 2>;
    using PieceMap = frozen::unordered_map<frozen::string, Piece::Kind, 6>;

    static ColorMap kColorMapping;
    static PieceMap kPieceMapping;

    static Piece::Kind KindFromString(const std::string &kind_str);
    static Piece::Color ColorFromString(const std::string &color_str);
};

#endif //CHESS_V2_PIECE_H
