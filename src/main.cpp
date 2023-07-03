#include "Controller/PieceViewRegistry.hpp"
#include "Data/Constants.hpp"
#include "Model/BoardPosition.hpp"
#include "Model/Chessboard.hpp"
#include "Model/MovePolicy.hpp"
#include "Model/PawnMovePolicy.hpp"
#include "Model/Piece.hpp"
#include "Model/PlayerKind.hpp"
#include "Model/PieceKind.hpp"
#include "Model/RookMovePolicy.hpp"
#include "View/ChessboardView.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "Data/TextureStore.hpp"
#include "Controller/Controller.hpp"
#include "View/PieceView.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <vector>

constexpr sf::Uint32 WINDOW_WIDTH = 1024;
constexpr sf::Uint32 WINDOW_HEIGHT = 1024;
constexpr uint FPS_LIMIT = 60;


void initLogging(const char *argv0) {
  fLB::FLAGS_logtostdout = true;
  google::InitGoogleLogging(argv0);
}

void initChessboard(Chessboard &board, PieceViewRegistry &piece_view_registry, const TextureStore &texture_store) {
  for (int32_t i = 0; i < 8; ++i) {
    board.insertPieceAt(Piece(PlayerKind::White, Constant::piece_order[i], i), BoardPosition{0, i});
    board.insertPieceAt(Piece(PlayerKind::White, PieceKind::Pawn, i + 8), BoardPosition{1, i});
    board.insertPieceAt(Piece(PlayerKind::Black, Constant::piece_order[i], i + 16), BoardPosition{7, i});
    board.insertPieceAt(Piece(PlayerKind::Black, PieceKind::Pawn, i + 24), BoardPosition{6, i});

    piece_view_registry.insert(i, PieceView(texture_store.textureForPiece(PlayerKind::White, Constant::piece_order[i])));
    piece_view_registry.insert(i + 8, PieceView(texture_store.textureForPiece(PlayerKind::White, PieceKind::Pawn)));
    piece_view_registry.insert(i + 16, PieceView(texture_store.textureForPiece(PlayerKind::Black, Constant::piece_order[i])));
    piece_view_registry.insert(i + 24, PieceView(texture_store.textureForPiece(PlayerKind::Black, PieceKind::Pawn)));
  }
}

int main(int argc, char *argv[]) {
  initLogging(argv[0]);
  LOG(INFO) << "Running application";

  const sf::VideoMode desktop_vm = sf::VideoMode::getDesktopMode();
  LOG(INFO) << "Desktop VideoMode: (" << desktop_vm.width << ", "
            << desktop_vm.height << ", " << desktop_vm.bitsPerPixel << ")";

  sf::VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
  sf::RenderWindow window(vm, "Simple Chess");
  window.setFramerateLimit(FPS_LIMIT);

  const TextureStore texture_store;
  Chessboard chessboard;
  PieceViewRegistry piece_view_registry;

  initChessboard(chessboard, piece_view_registry, texture_store);
  ChessboardView chessboard_view(vm.width, vm.height, texture_store);

  Controller controller(std::move(chessboard_view), std::move(chessboard), std::move(piece_view_registry), texture_store);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed) {
        controller.onMouseClicked(event.mouseButton);
      } else if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::Resized) {
        controller.onWindowResized(event.size);
        window.setView(
            sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
      }
    }

    window.clear(sf::Color::Black);
    window.draw(controller.chessboardView());
    window.draw(controller.pieceViews());
    window.display();
  }

  return 0;
}
