#include "SFML/Config.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include <array>
#include <glog/logging.h>

class Chessboard : public sf::Drawable {
public:
  constexpr static sf::Uint32 WIDTH = 8;
  constexpr static sf::Uint32 HEIGHT = 8;

  std::array<std::array<sf::RectangleShape, WIDTH>, HEIGHT> m_fields;

  Chessboard(sf::Uint32 tile_width_px, sf::Uint32 tile_height_px) {
    LOG(INFO) << "Chessboard ctor";

    for (sf::Uint32 i = 0; i < HEIGHT; ++i) {
      for (sf::Uint32 j = 0; j < WIDTH; ++j) {
        sf::RectangleShape &field = m_fields[i][j];
        const sf::Color tile_color =
            (i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black;
        field.setFillColor(tile_color);
        // field.setOutlineColor(sf::Color::Black);
        LOG(INFO) << "Tile (" << i << ", " << j << ") has position ("
                  << j * tile_width_px << ", " << i * tile_height_px << ") with color " << ((i + j) % 2 == 0 ? "White" : "Black");
        field.setPosition(j * tile_width_px, i * tile_height_px);
        field.setSize(sf::Vector2f(tile_width_px, tile_height_px));
      }
    }
  }

protected:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &field_row : m_fields) {
      for (const auto &field : field_row) {
        target.draw(field, states);
      }
    }
  }
};
