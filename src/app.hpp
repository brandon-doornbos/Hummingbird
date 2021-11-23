#ifndef _HB_APP
#define _HB_APP

#include <cstdlib>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

struct AppInfo
{
    uint32_t width;
    uint32_t height;
    const char* name;
};

class App
{
public:
    void run();
    App(AppInfo);
    ~App();

private:
    AppInfo m_app_info;
    GLFWwindow* m_window;
    VkInstance m_instance;

    void initWindow();
    void createInstance();
    void initVulkan();
    void mainLoop();
};

#endif