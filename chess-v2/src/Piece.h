#ifndef CHESS_V2_PIECE_H
#define CHESS_V2_PIECE_H

#include "PieceColor.h"
#include "PieceKind.h"


namespace chess {

class Piece {
public:
    Piece(const Piece &) = delete;
    Piece(Piece &&) = delete;
    Piece &operator=(const Piece &) = delete;
    Piece &operator=(Piece &&) = delete;

    explicit Piece(PieceColor color, PieceKind kind) noexcept;

    [[nodiscard]] PieceColor GetColor() const noexcept;
    [[nodiscard]] PieceKind GetKind() const noexcept;

private:
    PieceColor color_;
    PieceKind kind_;
};

}



#endif //CHESS_V2_PIECE_H
