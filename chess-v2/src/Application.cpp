//
// Created by kkafara on 5/31/24.
//

#include "Application.h"
#import <glog/logging.h>
#include "config/ConfigLoader.h"
#include <core/view/ViewGroup.h>


Application::Application(std::string application_name) :
        application_name_{std::move(application_name)},
        config_(ConfigLoader::LoadConfigFromFile("../config.json")) {
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

    ViewGroup root();

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Blue);


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
        window.draw(circle);
        window.display();
    }
}
