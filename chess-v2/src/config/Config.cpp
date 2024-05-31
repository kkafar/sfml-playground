//
// Created by kkafara on 5/31/24.
//

#include "Config.h"

Config::Config(fs::path assets_directory) :
        assets_path_{std::move(assets_directory)} {}

inline fs::path Config::GetAssetsDirectory() {
    return assets_path_;
}
