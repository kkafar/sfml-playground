#include <iostream>
#include <glog/logging.h>
#include <SFML/Graphics.hpp>
#include "model/board/Chessboard.h"

constexpr sf::Uint32 DEFAULT_WINDOW_WIDTH = 1024;
constexpr sf::Uint32 DEFAULT_WINDOW_HEIGHT = 1024;
constexpr sf::Uint32 DEFAULT_FPS = 60;

void InitLogging(const char *argv0) {
    fLB::FLAGS_logtostdout = true;
    google::InitGoogleLogging(argv0);
}

int main(int argc, char *argv[]) {
    InitLogging(argv[0]);
    LOG(INFO) << "Running application";

    const sf::VideoMode desktop_vm = sf::VideoMode::getDesktopMode();
    LOG(INFO) << "Desktop VideoMode: {" << desktop_vm.width << ", " << desktop_vm.height << "}";

    const sf::VideoMode video_mode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    sf::RenderWindow window(video_mode, "Simple chess v2");

    window.setFramerateLimit(DEFAULT_FPS);

    sf::Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
