#include "Application.h"
#import <glog/logging.h>
#include "config/ConfigLoader.h"
#include <core/view/View.h>
#include <core/scene/Scene.h>
#include <core/animation/AnimationDriver.h>
#include <core/animation/RotateAnimation.h>


Application::Application(std::string application_name) :
        application_name_{std::move(application_name)},
        config_(ConfigLoader::LoadConfigFromFile("config.json")) {
    InitLogging();
    assets_manager_.LoadAssetsFromDirectory(config_.GetImagesDirectory());
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

    auto circle = std::make_shared<sf::CircleShape>(100.f);
    circle->setFillColor(sf::Color::Blue);

    auto circle_2 = std::make_shared<sf::CircleShape>(300.f);
    circle_2->setFillColor(sf::Color::White);

    auto rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f {600, 600});
    rectangle->setFillColor(sf::Color::Red);

    LayoutParams params{{600, 600}, LayoutParams::Mode::kWrapContent, LayoutParams::Mode::kWrapContent};

    View::Shared root = std::make_shared<View>(params, rectangle);
    View view{params, circle};
    View view_2{params, circle_2};

    root->AddSubview(std::make_shared<View>(std::move(view)));
    root->AddSubview(std::make_shared<View>(std::move(view_2)));

    Scene scene{};
    scene.AddViewHierarchy(root);

    auto window_size = window.getSize();

    AnimationDriver animation_driver{};

    root->setPosition(300, 300);
    root->setOrigin(300, 300);
    RotateAnimation::Unique animation = std::make_unique<RotateAnimation>(root);
    animation->SetDurationMs(5000);
    animation->Start();
    animation_driver.RegisterAnimation(std::move(animation));

    sf::Clock clock{};
    sf::Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    window_size = window.getSize();
                    scene.GetRootViewRef()->InvalidateLayout();
                    break;
                }
                default:
                    break;
            }
        }

        sf::Time dt = clock.restart();

        animation_driver.RequestAnimationFrame(dt.asMilliseconds());
        scene.GetRootViewRef()->Layout({0, 0, static_cast<float>(window_size.x), static_cast<float>(window_size.y)});

        window.clear(sf::Color::Black);
        window.draw(scene);
        window.display();
    }
}
