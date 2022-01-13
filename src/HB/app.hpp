#ifndef _HB_APP
#define _HB_APP

#include <cstdint>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace HB {

struct AppInfo {
    uint32_t width;
    uint32_t height;
    char const* name;
};

class App {
public:
    void run();
    App(AppInfo);
    ~App();

private:
    std::vector<char const*> const m_validation_layers = {
        "VK_LAYER_KHRONOS_validation"
    };
#ifdef NDEBUG
    bool const m_enable_validation_layers = false;
#else
    bool const m_enable_validation_layers = true;
#endif
    AppInfo m_app_info;
    GLFWwindow* m_window;
    VkInstance m_instance;
    VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphics_queue;

    struct QueueFamilyIndices;

    bool checkValidationLayerSupport() const;
    void initWindow();
    void createInstance();
    void initVulkan();
    void pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    bool isDeviceSuitable(VkPhysicalDevice);
    void createLogicalDevice();
    void loop();
};

}

#endif
