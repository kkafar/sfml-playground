#include "PlayerKind.hpp"
#include <glog/logging.h>

std::string playerKindToString(PlayerKind kind) {
  switch (kind) {
  case PlayerKind::White:
    return "white";
  case PlayerKind::Black:
    return "black";
  default:
    LOG(ERROR) << "Unhandled PlayerKind";
    return "undefined";
  }
}
