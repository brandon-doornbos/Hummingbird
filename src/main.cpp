#include <cstdint>
#include <vector>

#include "app.hpp"
#include "config.hpp"

constexpr uint32_t const WIDTH = 1280;
constexpr uint32_t const HEIGHT = 720;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    HB::AppInfo app_info {};
    app_info.width = WIDTH;
    app_info.height = HEIGHT;
    app_info.name = APP_NAME;
    app_info.version = APP_VERSION;
    HB::App app { app_info };
    app.run();

    return 0;
}
