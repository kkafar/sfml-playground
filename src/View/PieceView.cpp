#include "PieceView.hpp"
#include "SFML/Graphics/Sprite.hpp"

PieceView::PieceView(const sf::Texture &texture, Tag tag) 
  : sf::Sprite(texture), m_tag(tag) {}

void PieceView::focus() {
  if (m_is_focused)
    return;

  m_is_focused = true;
  scale(2.0, 2.0);
}

void PieceView::blur() {
  if (!m_is_focused)
    return;

  m_is_focused = false;
  scale(0.5, 0.5);
}
