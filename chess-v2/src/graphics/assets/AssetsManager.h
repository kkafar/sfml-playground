//
// Created by kkafara on 6/1/24.
//

#ifndef CHESS_V2_ASSETSMANAGER_H
#define CHESS_V2_ASSETSMANAGER_H

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <unordered_map>
#include <optional>
#include <model/piece/Piece.h>

namespace fs = std::filesystem;

class AssetsManager {
public:
    using TextureShared = std::shared_ptr<sf::Texture>;
    using PieceTextureRegistry = std::unordered_map<Piece::Kind, TextureShared>;

    AssetsManager();

    bool LoadAssetsFromDirectory(const fs::path& assets_directory);

    /**
     * Crashes in case there is no texture loaded for given color / kind combination.
     * There is nothing more I can do anywhere else in the code to handle such error,
     * so I decided it is best to just crash here.
     */
    [[nodiscard]]
    TextureShared GetTexture(Piece::Color color, Piece::Kind kind);

private:
    static AssetsManager::TextureShared GetTextureFromRegistry(PieceTextureRegistry &registry, Piece::Kind kind) ;
    static bool InsertTextureToRegistry(PieceTextureRegistry &registry, Piece::Kind kind, TextureShared &&texture);

private:
    PieceTextureRegistry black_piece_registry_{};
    PieceTextureRegistry white_piece_registry_{};
};


#endif //CHESS_V2_ASSETSMANAGER_H
