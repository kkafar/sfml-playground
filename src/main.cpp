#include "Chessboard.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "TextureStore.hpp"
#include <SFML/Graphics.hpp>
#include <glog/logging.h>
#include <iostream>

constexpr sf::Uint32 WINDOW_WIDTH = 1024;
constexpr sf::Uint32 WINDOW_HEIGHT = 1024;

void initLogging(const char *argv0) {
  fLB::FLAGS_logtostdout = true;
  google::InitGoogleLogging(argv0);
}

int main(int argc, char *argv[]) {
  initLogging(argv[0]);
  LOG(INFO) << "Running application";

  const sf::VideoMode desktop_vm = sf::VideoMode::getDesktopMode();
  LOG(INFO) << "Desktop VideoMode: (" << desktop_vm.width << ", "
            << desktop_vm.height << ", " << desktop_vm.bitsPerPixel << ")";

  sf::VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
  sf::RenderWindow window(vm, "Simple Chess");
  window.setFramerateLimit(60);

  const TextureStore texture_store;
  Chessboard chessboard(vm.width, vm.height, texture_store);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::Resized) {
        // LOG(INFO) << "Window resized to (" << event.size.width << ", "
        //           << event.size.height << ")";
        chessboard.resize(event.size.width, event.size.height);
      }
    }

    window.clear(sf::Color::Black);
    window.draw(chessboard);
    window.display();
  }

  return 0;
}
