//
// Created by kkafara on 5/31/24.
//

#ifndef CHESS_V2_CONFIG_H
#define CHESS_V2_CONFIG_H

#include <filesystem>

namespace fs = std::filesystem;

class Config {
public:
    Config() = delete;
    Config(const Config &) = default;
    Config(Config &&) = default;
    Config(fs::path assets_directory);

    Config &operator=(const Config &) = default;
    Config &operator=(Config &&) = default;


    [[nodiscard]] fs::path GetAssetsDirectory();

private:
    fs::path assets_path_;
};


#endif //CHESS_V2_CONFIG_H
