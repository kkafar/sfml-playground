
#ifndef CHESS_V2_CHESSBOARD_H
#define CHESS_V2_CHESSBOARD_H

#include <optional>
#include <memory>
#include <array>
#include "BoardPosition.h"
#include "model/piece/Piece.h"

namespace chess::model::board {
    using namespace chess::model::piece;

    class Chessboard {
    public:
        using piece_ref_t = std::reference_wrapper<Piece>;
        using piece_shared_t = std::shared_ptr<Piece>;

        Chessboard();

        [[nodiscard]] std::optional<piece_ref_t> GetPieceRefAt(const BoardPosition &pos);

        std::optional<Piece> RemovePieceAt(const BoardPosition &pos);

        bool InsertPieceAt(Piece &&piece, const BoardPosition &pos);

        [[nodiscard]] bool IsTileEmpty(const BoardPosition &pos) const;

        bool MovePiece(const BoardPosition &from_pos, const BoardPosition &to_pos);

    private:
        std::array<std::array<std::optional<Piece>, 8>, 8> board_;
    };

}


#endif //CHESS_V2_CHESSBOARD_H
