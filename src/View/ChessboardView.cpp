#include "ChessboardView.hpp"
#include "SFML/System/Vector2.hpp"

ChessboardView::ChessboardView(const sf::Uint32 width_px, const sf::Uint32 height_px,
                       const TextureStore &texture_store)
    : m_width_px(width_px), m_height_px(height_px),
      m_tile_width_px(width_px / WIDTH), m_tile_height_px(height_px / HEIGHT)
{
  LOG(INFO) << "Chessboard ctor";

  for (sf::Uint32 i = 0; i < HEIGHT; ++i) {
    for (sf::Uint32 j = 0; j < WIDTH; ++j) {
      sf::RectangleShape &field = m_fields[i][j];
      const sf::Color tile_color =
          (i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black;
      field.setFillColor(tile_color);
      field.setPosition(j * m_tile_width_px, i * m_tile_height_px);
      field.setSize(sf::Vector2f(m_tile_width_px, m_tile_height_px));
    }
  }
}

void ChessboardView::resize(const sf::Uint32 width_px, const sf::Uint32 height_px) {
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
}

void ChessboardView::draw(sf::RenderTarget &target,
                              sf::RenderStates states) const {
  for (const auto &field_row : m_fields) {
    for (const auto &field : field_row) {
      target.draw(field, states);
    }
  }
}

sf::Vector2u ChessboardView::getSize() const {
  return {m_width_px, m_height_px};
}

sf::Vector2u ChessboardView::getTileSize() const {
  return {m_tile_width_px, m_tile_height_px};
}

void ChessboardView::tintPossibleMoves(const Piece &piece, const std::vector<Move> &moves) {
  
}
