//
// Created by kkafara on 5/31/24.
//

#include "Application.h"

#include <utility>

#import <glog/logging.h>

Application::Application(std::string application_name) : application_name_{std::move(application_name)} {
    InitLogging();
}

void Application::InitLogging() {
    fLB::FLAGS_logtostdout = true;
    google::InitGoogleLogging(application_name_.c_str());
}

void Application::Run() {
    LOG(INFO) << "Running application";
    const sf::VideoMode video_mode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    sf::RenderWindow window(video_mode, "SimpleChess v2");

    window.setFramerateLimit(DEFAULT_FPS);

    sf::Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }
}
