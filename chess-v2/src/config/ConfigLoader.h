//
// Created by kkafara on 5/31/24.
//

#ifndef CHESS_V2_CONFIGLOADER_H
#define CHESS_V2_CONFIGLOADER_H

#include <filesystem>
#include "Config.h"

namespace fs = std::filesystem;

class ConfigLoader {
public:
    ConfigLoader() = delete;
    ConfigLoader(const ConfigLoader &) = delete;
    ConfigLoader(ConfigLoader &&) = delete;

    [[nodiscard("Config should not be discarded")]]
    static Config LoadConfigFromFile(fs::path config_path);

private:
};


#endif //CHESS_V2_CONFIGLOADER_H
