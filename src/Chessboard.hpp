#ifndef __CHESSBOARD_HPP__
#define __CHESSBOARD_HPP__

#include "PieceKind.hpp"
#include "PlayerKind.hpp"
#include "PlayerPieces.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "TextureStore.hpp"
#include <array>
#include <glog/logging.h>

class Chessboard : public sf::Drawable {
public:
  constexpr static sf::Uint32 WIDTH = 8;
  constexpr static sf::Uint32 HEIGHT = 8;

  Chessboard(const sf::Uint32 width_px, const sf::Uint32 height_px,
             const TextureStore &texture_store)
      : m_width_px(width_px), m_height_px(height_px),
        m_player_white(PlayerKind::White, width_px / WIDTH, height_px / HEIGHT, texture_store),
        m_player_black(PlayerKind::Black, width_px / WIDTH, height_px / HEIGHT, texture_store) {
    LOG(INFO) << "Chessboard ctor";

    sf::Uint32 tile_width_px = width_px / WIDTH;
    sf::Uint32 tile_height_px = height_px / HEIGHT;

    for (sf::Uint32 i = 0; i < HEIGHT; ++i) {
      for (sf::Uint32 j = 0; j < WIDTH; ++j) {
        sf::RectangleShape &field = m_fields[i][j];
        const sf::Color tile_color =
            (i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black;
        field.setFillColor(tile_color);
        field.setPosition(j * tile_width_px, i * tile_height_px);
        field.setSize(sf::Vector2f(tile_width_px, tile_height_px));
      }
    }
  }

  void resize(const sf::Uint32 width_px, const sf::Uint32 height_px) {
    if (m_width_px == width_px && m_height_px == height_px) {
      return;
    }

    m_width_px = width_px;
    m_height_px = height_px;

    sf::Uint32 tile_width_px = m_width_px / WIDTH;
    sf::Uint32 tile_height_px = m_height_px / HEIGHT;

    for (sf::Uint32 i = 0; i < HEIGHT; ++i) {
      for (sf::Uint32 j = 0; j < WIDTH; ++j) {
        sf::RectangleShape &field = m_fields[i][j];
        field.setSize(sf::Vector2f(tile_width_px, tile_height_px));
        field.setPosition(j * tile_width_px, i * tile_height_px);
      }
    }

    m_player_black.resize(width_px, height_px);
    m_player_white.resize(width_px, height_px);
  }

protected:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &field_row : m_fields) {
      for (const auto &field : field_row) {
        target.draw(field, states);
      }
    }

    target.draw(m_player_white);
    target.draw(m_player_black);
  }

private:
  std::array<std::array<sf::RectangleShape, WIDTH>, HEIGHT> m_fields;

  sf::Uint32 m_width_px;
  sf::Uint32 m_height_px;

  PlayerPieces m_player_white;
  PlayerPieces m_player_black;
};

#endif // !__CHESSBOARD_HPP__
