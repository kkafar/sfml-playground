#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <glog/logging.h>
#include "chessboard.hpp"

void initLogging(const char *argv0) {
  fLB::FLAGS_logtostdout = true;
  google::InitGoogleLogging(argv0);
}

int main (int argc, char *argv[]) {
  initLogging(argv[0]);
  LOG(INFO) << "Running application";

  sf::RenderWindow window(sf::VideoMode(640, 640), "SFML works!");
  Chessboard chessboard(80, 80);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);
    window.draw(chessboard);
    window.display();
  }

  return 0;
}
