#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main (int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
  sf::CircleShape circle_shape(100.f);
  circle_shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);
    window.draw(circle_shape);
    window.display();
  }

  return 0;
}
