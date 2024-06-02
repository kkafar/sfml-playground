//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_TEXTUREMANAGER_H
#define CHESS_V2_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;

class TextureManager {
public:
    TextureManager();

    bool LoadTexturesFromDirectory(fs::path assets_directory);

private:
};


#endif //CHESS_V2_TEXTUREMANAGER_H
