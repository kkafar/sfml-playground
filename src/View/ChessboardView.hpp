#ifndef __CHESSBOARD_VIEW_HPP__
#define __CHESSBOARD_VIEW_HPP__

#include "Model/PlayerKind.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "View/Resizable.hpp"
#include <Data/TextureStore.hpp>
#include <Model/PieceKind.hpp>
#include <array>
#include <glog/logging.h>

class ChessboardView : public sf::Drawable, public Resizable {
public:
  constexpr static sf::Uint32 WIDTH = 8;
  constexpr static sf::Uint32 HEIGHT = 8;

  ChessboardView(const sf::Uint32 width_px, const sf::Uint32 height_px,
                 const TextureStore &texture_store);

  void resize(const sf::Uint32 width_px, const sf::Uint32 height_px);

  [[nodiscard]] sf::Vector2u getSize() const;

  [[nodiscard]] sf::Vector2u getTileSize() const;

protected:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
  std::array<std::array<sf::RectangleShape, WIDTH>, HEIGHT> m_fields;

  sf::Uint32 m_width_px;
  sf::Uint32 m_height_px;
  sf::Uint32 m_tile_width_px;
  sf::Uint32 m_tile_height_px;

  // PlayerPieces m_player_white;
  // PlayerPieces m_player_black;
};

#endif // !__CHESSBOARD_VIEW_HPP__
