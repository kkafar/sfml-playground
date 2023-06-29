#include "MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include "PieceKind.hpp"

MovePolicy::MovePolicy(PieceKind piece_kind) : m_kind(piece_kind) {}
