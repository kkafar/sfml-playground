//
// Created by kkafara on 5/31/24.
//

#include "ConfigLoader.h"

#include <cstdio>
#include <cassert>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <core/CommonTypes.h>


using namespace rapidjson;

class FileRAIIContainer {
public:
    /// This should be the owning pointer.
    FileRAIIContainer(const fs::path& file_path) {
        file_ = std::fopen(file_path.c_str(), "rb");
    }

    ~FileRAIIContainer() {
        fclose(file_);
    }

    [[nodiscard]] FILE *GetRawFile() const {
        return file_;
    }

    [[nodiscard]] bool IsValid() const noexcept {
        return file_ != nullptr;
    }

private:
    std::FILE *file_;
    bool open_success_{false};
};

Config ConfigLoader::LoadConfigFromFile(fs::path config_path) {
    FileRAIIContainer fileContainer(config_path);
    assert(fileContainer.IsValid());

    Byte readBuffer[1 << 12];
    auto input_stream = FileReadStream(fileContainer.GetRawFile(), readBuffer, sizeof(readBuffer));

    Document document;
    document.ParseStream(input_stream);

    assert(document.HasMember("assetsDir"));
    assert(document["assetsDir"].GetType() == Type::kStringType);
    auto assets_dir = fs::path(document["assetsDir"].GetString());

    return {assets_dir};
}
