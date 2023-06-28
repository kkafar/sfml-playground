#ifndef __TEXTURE_STORE_HPP__
#define __TEXTURE_STORE_HPP__

#include "Model/PieceKind.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "glog/logging.h"
#include <filesystem>
#include <unordered_map>
#include <vector>

class TextureStore {
public:
  std::unordered_map<std::string, sf::Texture> store;

  TextureStore() {
    std::vector<std::string> colors{"white"};
    std::vector<std::string> piece_names{"pawn", "queen",  "rook",
                                         "king", "bishop", "knight"};
    std::vector<std::string> paths;

    for (const auto &piece_name : piece_names) {
      for (const auto &color : colors) {
        sf::Texture texture;
        std::string path =
            "/home/kkafara/workspace/playground/sfml/balls/assets/images/" +
            piece_name + "-" + color + "-1.png";
        if (!texture.loadFromFile(path)) {
          LOG(ERROR) << "Failed to load texture at " << path;
        } else {
          store.insert({piece_name, texture});
        }
      }
    }
  }

  // Texture store retains all textures
  const sf::Texture &textureForPieceKind(PieceKind piece_kind) const {
    const sf::Texture &texture = store.at(pieceKindToString(piece_kind));
    return texture;
  }

private:
};

#endif // !__TEXTURE_STORE_HPP__
