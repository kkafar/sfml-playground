//
// Created by kkafara on 5/31/24.
//

#ifndef CHESS_V2_CONFIG_H
#define CHESS_V2_CONFIG_H

#include <filesystem>

namespace fs = std::filesystem;

class Config {
public:
    Config() = default;
    Config(const Config &) = default;
    Config(Config &&) = default;

    Config &operator=(const Config &) = default;
    Config &operator=(Config &&) = default;


    [[nodiscard]] const fs::path &GetAssetsDirectory();
    [[nodiscard]] const fs::path &GetImagesDirectory();
    [[nodiscard]] const fs::path &GetFontsDirectory();

private:
    friend class ConfigLoader;

    fs::path assets_path_{};
    fs::path images_path_{};
    fs::path fonts_path_{};
};


#endif //CHESS_V2_CONFIG_H
