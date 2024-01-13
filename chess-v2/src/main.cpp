#include <iostream>
#include <glog/logging.h>
#include <SFML/Graphics.hpp>

void InitLogging(const char *argv0) {
    fLB::FLAGS_logtostdout = true;
    google::InitGoogleLogging(argv0);
}


int main(int argc, char *argv[]) {
    InitLogging(argv[0]);
    LOG(INFO) << "Running application";

    const sf::VideoMode desktop_vm = sf::VideoMode::getDesktopMode();
    LOG(INFO) << "Desktop VideoMode: {" << desktop_vm.width << ", " << desktop_vm.height << "}";

    return 0;
}
