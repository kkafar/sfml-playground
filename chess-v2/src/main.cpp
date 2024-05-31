#include "Application.h"

int main(int argc, char *argv[]) {
    Application(std::string{argv[0]}).Run();
    return 0;
}
