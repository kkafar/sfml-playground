//
// Created by kkafara on 5/31/24.
//

#include "Config.h"

const fs::path & Config::GetAssetsDirectory() {
    return assets_path_;
}

const fs::path &Config::GetImagesDirectory() {
    return images_path_;
}

const fs::path &Config::GetFontsDirectory() {
    return fonts_path_;
}
