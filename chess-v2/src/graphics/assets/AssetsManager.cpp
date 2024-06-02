#include "AssetsManager.h"
#include <cassert>
#include <ranges>
#include <array>
#include <glog/logging.h>

struct AssetDescription {

};


AssetsManager::AssetsManager() {

}


bool AssetsManager::LoadAssetsFromDirectory(const fs::path& assets_directory) {
    LOG(INFO) << "cwd" << fs::current_path() << "\n";
    LOG(INFO) << "Assets directory " << assets_directory << "\n";
    assert(fs::is_directory(assets_directory));

    // TODO: Reorganize & cleanup this code
    for (auto &file : fs::directory_iterator(assets_directory)) {
        if (!fs::is_regular_file(file)) {
            continue;
        }

        const auto &path = file.path();
        /// Could not find easy way to convert path to some kind of view
        const auto file_name = std::string(path.stem());

        // Files are named with following schema:
        // <figure-type>-<color>-<family-tag>
        // There are currently 3 sets of assets, each with different style
        // and family-tag is the id of these sets.

        const auto dash_count = std::ranges::count(file_name, '-');

        // We expect exactly two dashes, see above ^
        if (dash_count != 2) {
            continue;
        }

        LOG(INFO) << "Processing asset with name: " << file_name << '\n';

        std::vector<std::string> name_parts{};
        name_parts.reserve(3);
        auto splitted_name_view = std::views::split(file_name, '-');
        for (auto &&part : splitted_name_view) {
            name_parts.emplace_back(part.begin(), part.end());
        }

        assert(name_parts.size() == 3);
        const std::string &figure_name = name_parts[0];
        const std::string &color_name = name_parts[1];
        const std::string &family_id_str = name_parts[2];

        Piece::Kind kind = PieceUtil::KindFromString(figure_name);
        Piece::Color color = PieceUtil::ColorFromString(color_name);
        int family_id = std::stoi(family_id_str);

        // Hardcoded for now.
        // TODO: Move this to config file
        if (family_id != 1) {
            continue;
        }

        auto texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(path)) {
            LOG(FATAL) << "Failed to load texture for " << color_name << " " << figure_name << " " << family_id_str << "\n";
        }

        LOG(INFO) << "Successfully loaded texture for " << color_name << " " << figure_name << " " << family_id_str << "\n";
        if (color == Piece::Color::kWhite) {
            InsertTextureToRegistry(white_piece_registry_, kind, std::move(texture));
        } else {
            InsertTextureToRegistry(black_piece_registry_, kind, std::move(texture));
        }
    }

    return false;
}

AssetsManager::TextureShared AssetsManager::GetTexture(Piece::Color color, Piece::Kind kind) {
    switch (color) {
        case Piece::Color::kWhite:
            return GetTextureFromRegistry(white_piece_registry_, kind);
        case Piece::Color::kBlack:
            return GetTextureFromRegistry(black_piece_registry_, kind);
        default:
            LOG(FATAL) << "Unexpected figure color received\n";
    }
}

AssetsManager::TextureShared
AssetsManager::GetTextureFromRegistry(PieceTextureRegistry &registry, Piece::Kind kind) {
    return registry[kind];
}

bool AssetsManager::InsertTextureToRegistry(AssetsManager::PieceTextureRegistry &registry, Piece::Kind kind, AssetsManager::TextureShared &&texture) {
    return registry.insert({kind, std::move(texture)}).second;
}
