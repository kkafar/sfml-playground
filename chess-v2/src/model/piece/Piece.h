#ifndef CHESS_V2_PIECE_H
#define CHESS_V2_PIECE_H

#include "PieceColor.h"
#include "PieceKind.h"
#include <core/CommonTypes.h>


namespace chess::model::piece {

    class Piece {
    public:
        Piece(const Piece &) = delete;

        Piece(Piece &&) = default;

        Piece &operator=(const Piece &) = delete;

        Piece &operator=(Piece &&) = default;

        explicit Piece(PieceColor color, PieceKind kind) noexcept;

        [[nodiscard]] PieceColor GetColor() const noexcept;

        [[nodiscard]] PieceKind GetKind() const noexcept;

        void SetTag(Tag tag) noexcept;
        [[nodiscard]] Tag GetTag() const noexcept;

    private:
        PieceColor color_;
        PieceKind kind_;
        Tag tag_;
    };

}


#endif //CHESS_V2_PIECE_H
