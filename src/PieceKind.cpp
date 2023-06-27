#include "PieceKind.hpp"
#include <glog/logging.h>

std::string pieceKindToString(PieceKind kind) {
  switch (kind) {
  case PieceKind::Pawn:
    return "pawn";
  case PieceKind::Rook:
    return "rook";
  case PieceKind::Queen:
    return "queen";
  case PieceKind::Knight:
    return "knight";
  case PieceKind::King:
    return "king";
  case PieceKind::Bishop:
    return "bishop";
  default:
    LOG(ERROR) << "Unhandled piece kind";
    return "unknown";
  }
}
