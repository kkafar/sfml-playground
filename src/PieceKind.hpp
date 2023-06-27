#ifndef __PIECE_KIND_HPP__
#define __PIECE_KIND_HPP__

#include <string>

enum class PieceKind {
  Pawn,
  Bishop,
  King,
  Knight,
  Queen,
  Rook,
};

std::string pieceKindToString(PieceKind kind);

#endif // !__PIECE_KIND_HPP__
