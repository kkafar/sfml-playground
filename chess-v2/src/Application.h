//
// Created by kkafara on 5/31/24.
//

#ifndef CHESS_V2_APPLICATION_H
#define CHESS_V2_APPLICATION_H

#include <glog/logging.h>
#include <SFML/Graphics.hpp>

constexpr sf::Uint32 DEFAULT_WINDOW_WIDTH = 1024;
constexpr sf::Uint32 DEFAULT_WINDOW_HEIGHT = 1024;
constexpr sf::Uint32 DEFAULT_FPS = 60;

class Application final {
public:
    Application() = delete;

    Application(std::string application_name);

    void Run();

private:
    void InitLogging();

    void InitModel();
    void InitViews();

    std::string application_name_;
};


#endif //CHESS_V2_APPLICATION_H
