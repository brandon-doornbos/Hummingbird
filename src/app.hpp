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
    std::vector<char const*> const m_device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    AppInfo m_app_info;
    GLFWwindow* m_window;
    VkInstance m_instance;
    VkSurfaceKHR m_surface;
    VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphics_queue;
    VkQueue m_present_queue;
    VkSwapchainKHR m_swap_chain;
    std::vector<VkImage> m_swap_chain_images;
    VkFormat m_swap_chain_image_format;
    VkExtent2D m_swap_chain_extent;
    std::vector<VkImageView> m_swap_chain_image_views;
    VkPipelineLayout m_pipeline_layout;
    VkRenderPass m_render_pass;
    VkPipeline m_graphics_pipeline;
    std::vector<VkFramebuffer> m_swap_chain_framebuffers;
    VkCommandPool m_command_pool;
    VkCommandBuffer m_command_buffer;

    struct QueueFamilyIndices;
    struct SwapChainSupportDetails;

    bool check_validation_layer_support() const;
    void init_window();
    void create_instance();
    void create_surface();
    void init_vulkan();
    void pick_physical_device();
    QueueFamilyIndices find_queue_families(VkPhysicalDevice) const;
    bool check_device_extension_support(VkPhysicalDevice) const;
    SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice) const;
    VkSurfaceFormatKHR choose_swap_surface_format(std::vector<VkSurfaceFormatKHR> const&) const;
    VkPresentModeKHR choose_swap_present_mode(std::vector<VkPresentModeKHR> const&) const;
    VkExtent2D choose_swap_extent(VkSurfaceCapabilitiesKHR const&) const;
    bool is_device_suitable(VkPhysicalDevice);
    void create_logical_device();
    void create_swap_chain();
    void create_image_views();
    VkShaderModule create_shader_module(std::vector<char> const& source) const;
    void create_render_pass();
    void create_graphics_pipeline();
    void create_framebuffers();
    void create_command_pool();
    void create_command_buffer();
    void loop();
};

}

#endif
