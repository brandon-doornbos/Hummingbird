#define PROJECT_NAME "hummingbird"

#include <iostream>
#include <cstdlib>

#include "app.hpp"

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    AppInfo app_info = { WIDTH, HEIGHT, PROJECT_NAME };
    App app = App(app_info);
    app.run();

    return 0;
}