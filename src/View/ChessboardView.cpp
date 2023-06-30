#include "ChessboardView.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <optional>
#include <vector>

const sf::Color ChessboardView::s_black_field_color = sf::Color(86, 65, 56, 255);
const sf::Color ChessboardView::s_white_field_color = sf::Color(247, 243, 227, 255);
const sf::Color ChessboardView::s_tint_attack_color = sf::Color(203, 128, 125, 100);
const sf::Color ChessboardView::s_tint_move_color = sf::Color(67, 170, 139, 100);
const sf::Color ChessboardView::s_tint_blocked_color = sf::Color(187, 159, 6, 100);

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
          (i + j) % 2 == 0 ? s_white_field_color : s_black_field_color;
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
  m_tile_width_px = m_width_px / WIDTH;
  m_tile_height_px = m_height_px / HEIGHT;

  for (sf::Uint32 i = 0; i < HEIGHT; ++i) {
    for (sf::Uint32 j = 0; j < WIDTH; ++j) {
      sf::RectangleShape &field = m_fields[i][j];
      field.setSize(sf::Vector2f(m_tile_width_px, m_tile_height_px));
      field.setPosition(j * m_tile_width_px, i * m_tile_height_px);
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

  if (m_show_tint_rects) {
    for (const auto &field_row : m_tint_rects) {
      for (const auto &field : field_row) {
        if (field) {
          target.draw(field.value(), states);
        }
      }
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
  for (const Move &move : moves) {
    sf::RectangleShape field = sf::RectangleShape(sf::Vector2f(m_tile_width_px, m_tile_height_px));
    field.setPosition(move.pos.col * m_tile_width_px, move.pos.row * m_tile_height_px);
    switch (move.kind) {
      case Move::Kind::Normal: 
        field.setFillColor(s_tint_move_color);
        break;
      case Move::Kind::Attack:
        field.setFillColor(s_tint_attack_color);
        break;
      case Move::Kind::Blocked:
      case Move::Kind::Invalid:
        // field.setFillColor(s_tint_blocked_color);
        break;
    }
    m_tint_rects[move.pos.row][move.pos.col]  = std::make_optional(std::move(field));
  }
  m_show_tint_rects = true;
}

void ChessboardView::clearMoveTints(const std::vector<Move> &moves) {
  for (const Move &move : moves) {
    m_tint_rects[move.pos.row][move.pos.col] = std::nullopt;
  }
  m_show_tint_rects = false; 
}
