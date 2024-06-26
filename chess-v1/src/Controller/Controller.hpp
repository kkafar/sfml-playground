#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

#include "Controller/PieceViewRegistry.hpp"
#include "Data/TextureStore.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/Move.hpp"
#include "Model/PlayerKind.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "View/ChessboardView.hpp"
#include <functional>
#include <optional>
#include <vector>

class Controller {
public:
  Controller(ChessboardView &&board_view, Chessboard &&board, PieceViewRegistry &&pvr, const TextureStore &texture_store);

  void onMouseClicked(const sf::Event::MouseButtonEvent &event);
  void onWindowResized(const sf::Event::SizeEvent &event);

  inline const ChessboardView &chessboardView() { return m_board_view; }
  inline const PieceViewRegistry &pieceViews() { return m_piece_view_registry; }

private:
  ChessboardView m_board_view;
  Chessboard m_board;
  PieceViewRegistry m_piece_view_registry;
  TextureStore m_texture_store;
  std::optional<std::reference_wrapper<Piece>> m_focused_piece{std::nullopt};
  std::vector<Move> m_focused_piece_move_buf;
  PlayerKind m_active_player{PlayerKind::White};


  BoardPosition translateWindowCoordinatesToBoardPosition(int x, int y) const;
  sf::Vector2u translateBoardPositionToWindowCoordinates(BoardPosition pos) const;

  void focusPiece(Piece &piece);
  void blurFocusedPiece();
  void movePiece(Piece &piece, const Move &move);
  void performPlayerMove(Piece &piece, const Move &move);
  
  /// This method effectively drops object that the passed reference points to.
  /// Do not use passed reference anymore.
  void removePiece(Piece &piece);

  std::optional<Move> positionIsInMoves(const BoardPosition &pos, const std::vector<Move> &moves) const;
  void togglePlayer();
};

#endif // !__CONTROLLER_HPP__
