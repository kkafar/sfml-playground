#ifndef __PIECE_VIEW_HPP__
#define __PIECE_VIEW_HPP__

#include "SFML/Config.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "View/Resizable.hpp"

class PieceView : public sf::Sprite {
public:
  using sf::Sprite::Sprite;
  using Tag = sf::Uint32;

  PieceView(const sf::Texture &texture, Tag tag);

  [[nodiscard]] inline Tag tag() { return m_tag; };

  inline void setTag(Tag tag) { m_tag = tag; }

  [[nodiscard]] inline bool isFocused() { return m_is_focused; }

  void focus();
  void blur();

private:
  Tag m_tag;
  bool m_is_focused{false};

};

#endif // !__PIECE_VIEW_HPP__
