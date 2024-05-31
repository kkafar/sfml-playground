//
// Created by kkafara on 1/13/24.
//

#include <glog/logging.h>
#include "Chessboard.h"

namespace chess::model::board {
    using namespace chess::model::piece;

    Chessboard::Chessboard() = default;

    std::optional<Chessboard::piece_ref_t> Chessboard::GetPieceRefAt(const BoardPosition &pos) {
        std::optional<Piece> &piece_opt = board_[pos.row][pos.col];

        if (piece_opt) {
            LOG(INFO) << "Piece found at " << pos;
            return std::make_optional<Chessboard::piece_ref_t>(std::ref(piece_opt.value()));
        }

        return std::nullopt;
    }

    std::optional<chess::model::piece::Piece> Chessboard::RemovePieceAt(const BoardPosition &pos) {
        std::optional<Piece> ret_val{std::move(board_[pos.row][pos.col])};
        board_[pos.row][pos.col] = std::nullopt;
        return ret_val;
    }

    bool Chessboard::InsertPieceAt(Piece &&piece, const BoardPosition &pos) {
        if (board_[pos.row][pos.col]) {
            return false;
        }
        board_[pos.row][pos.col] = std::make_optional<Piece>(std::forward<Piece>(piece));
        return true;
    }

    inline bool Chessboard::IsTileEmpty(const BoardPosition &pos) const {
        return !board_[pos.row][pos.col].has_value();
    }

    bool Chessboard::MovePiece(const BoardPosition &from_pos, const BoardPosition &to_pos) {
        std::optional<Piece> piece_opt = this->RemovePieceAt(from_pos);
        if (!piece_opt.has_value()) {
            LOG(ERROR) << "[Chessboard::MovePiece] Piece not found at position " << from_pos;
            return false;
        }

        return this->InsertPieceAt(std::move(piece_opt.value()), to_pos);
    }


}


