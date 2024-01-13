#ifndef __PLAYER_KIND_HPP__
#define __PLAYER_KIND_HPP__

#include <string>

enum class PlayerKind {
  White,
  Black,
};

std::string playerKindToString(PlayerKind kind);

#endif // !__PLAYER_KIND_HPP__
