#include <iostream>
#include <glog/logging.h>
#include <SFML/Graphics.hpp>
#include "Application.h"

void InitLogging(const char *argv0) {
    fLB::FLAGS_logtostdout = true;
    google::InitGoogleLogging(argv0);
}

int main(int argc, char *argv[]) {
    InitLogging(argv[0]);
    LOG(INFO) << "Running application";

    Application(std::string{argv[0]}).Run();

    return 0;
}
