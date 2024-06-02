#include "TextureManager.h"
#include <cassert>
#include <ranges>
#include <array>

struct AssetDescription {

};


TextureManager::TextureManager() {

}


bool TextureManager::LoadTexturesFromDirectory(fs::path assets_directory) {
    assert(fs::is_directory(assets_directory));

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

        std::vector<std::string> name_parts(3);
        auto splitted_name_view = std::views::split(file_name, '-');
        for (auto &&part : splitted_name_view) {
            name_parts.emplace_back(part.begin(), part.end());
        }
        assert(name_parts.size() == 3);
        const std::string &figure_name = name_parts[0];
        const std::string &color = name_parts[1];
        const std::string &family_id = name_parts[2];

    }

    return false;
}
