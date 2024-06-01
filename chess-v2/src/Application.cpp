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

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Blue);

    sf::CircleShape circle_2(300.f);
    circle.setFillColor(sf::Color::Blue);

    sf::RectangleShape rect({600, 600});
    rect.setFillColor(sf::Color::Red);

    ViewGroup root{0, std::make_shared<sf::RectangleShape>(std::move(rect))};
    View view{1, ViewType::kView, std::make_shared<sf::CircleShape>(std::move(circle))};
    View view_2{1, ViewType::kView, std::make_shared<sf::CircleShape>(std::move(circle_2))};

    root.GetTransform().rotate(45.f);

    root.AddSubview(std::make_shared<View>(std::move(view_2)));
    root.AddSubview(std::make_shared<View>(std::move(view)));

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
        window.draw(root);
        window.display();
    }
}
