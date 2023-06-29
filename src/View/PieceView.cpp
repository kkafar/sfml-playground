#include "PieceView.hpp"
#include "SFML/Graphics/Sprite.hpp"

PieceView::PieceView(const sf::Texture &texture, Tag tag) 
  : sf::Sprite(texture), m_tag(tag) {}

