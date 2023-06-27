#ifndef __RESIZABLE_HPP__
#define __RESIZABLE_HPP__

#include "SFML/Config.hpp"

class Resizable {
public:
  virtual void resize(const sf::Uint32 width_px, const sf::Uint32 height_px) = 0;
};

#endif // !__RESIZABLE_HPP__
