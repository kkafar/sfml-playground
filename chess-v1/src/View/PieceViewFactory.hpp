#ifndef __PIECE_VIEW_FACTORY_HPP__
#define __PIECE_VIEW_FACTORY_HPP__

#include "Model/PieceKind.hpp"
#include "Model/PlayerKind.hpp"
#include "View/PieceView.hpp"

class PieceViewFactory {
public:
  static PieceView viewForPiece(const PlayerKind color, const PieceKind kind);
};

#endif // !__PIECE_VIEW_FACTORY_HPP__
