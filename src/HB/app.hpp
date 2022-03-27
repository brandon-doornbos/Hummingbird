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
    VkSurfaceKHR m_surface;
    VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphics_queue;
    VkQueue m_present_queue;

    struct QueueFamilyIndices;

    bool check_validation_layer_support() const;
    void init_window();
    void create_instance();
    void create_surface();
    void init_vulkan();
    void pick_physical_device();
    QueueFamilyIndices find_queue_families(VkPhysicalDevice);
    bool is_device_suitable(VkPhysicalDevice);
    void create_logical_device();
    void loop();
};

}

#endif
