#include <cstring>
#include <optional>
#include <set>
#include <stdexcept>

#include "app.hpp"

namespace HB {

void App::run()
{
    loop();
}

App::App(AppInfo app_info)
    : m_app_info(app_info)
{
    initWindow();
    initVulkan();
}

App::~App()
{
    vkDestroyDevice(m_device, nullptr);
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    vkDestroyInstance(m_instance, nullptr);

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool App::checkValidationLayerSupport() const
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (char const* layerName : m_validation_layers) {
        bool layerFound = false;

        for (auto const& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

void App::initWindow()
{
    if (glfwInit() != GLFW_TRUE)
        throw std::runtime_error("Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_app_info.width, m_app_info.height, m_app_info.name, nullptr, nullptr);
    if (m_window == NULL)
        throw std::runtime_error("Failed to create a window!");
}

void App::createInstance()
{
    if (m_enable_validation_layers && !checkValidationLayerSupport())
        throw std::runtime_error("validation layers requested, but not available!");

    // VkApplicationInfo vkAppInfo{};
    // vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // vkAppInfo.pApplicationName = m_app_info.name;
    // vkAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    // vkAppInfo.pEngineName = "No Engine";
    // vkAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    // vkAppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    char const** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if (glfwExtensions == NULL)
        throw std::runtime_error("Failed to get required extensions.");

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    if (m_enable_validation_layers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validation_layers.size());
        createInfo.ppEnabledLayerNames = m_validation_layers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
        throw std::runtime_error("failed to create instance!");

    // https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
    // Checking for extension support
}

void App::createSurface()
{
    if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
        throw std::runtime_error("failed to create window surface!");
}

void App::initVulkan()
{
    createInstance();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
}

void App::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    if (deviceCount == 0)
        throw std::runtime_error("failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    for (VkPhysicalDevice const& device : devices) {
        if (isDeviceSuitable(device)) {
            m_physical_device = device;
            break;
        }
    }

    if (m_physical_device == VK_NULL_HANDLE)
        throw std::runtime_error("failed to find a suitable GPU!");
}

struct App::QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool isComplete()
    {
        return graphics_family.has_value() && present_family.has_value();
    }
};

App::QueueFamilyIndices App::findQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    int i = 0;
    for (VkQueueFamilyProperties const& queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphics_family = i;

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &present_support);
        if (present_support)
            indices.present_family = i;

        if (indices.isComplete())
            break;

        i++;
    }

    return indices;
}

bool App::isDeviceSuitable(VkPhysicalDevice device)
{
    // VkPhysicalDeviceProperties deviceProperties;
    // VkPhysicalDeviceFeatures deviceFeatures;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    // return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
    //        deviceFeatures.geometryShader;
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.isComplete();
}

void App::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(m_physical_device);

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::set<uint32_t> unique_queue_families = { indices.graphics_family.value(), indices.present_family.value() };

    float queue_priority = 1.0f;
    for (uint32_t queue_family : unique_queue_families) {
        VkDeviceQueueCreateInfo queue_create_info {};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = queue_family;
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(queue_create_info);
    }

    VkPhysicalDeviceFeatures device_features {};

    VkDeviceCreateInfo create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
    create_info.pQueueCreateInfos = queue_create_infos.data();

    create_info.pEnabledFeatures = &device_features;

    create_info.enabledExtensionCount = 0;

    if (m_enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(m_validation_layers.size());
        create_info.ppEnabledLayerNames = m_validation_layers.data();
    } else {
        create_info.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_physical_device, &create_info, nullptr, &m_device) != VK_SUCCESS)
        throw std::runtime_error("failed to create logical device!");

    vkGetDeviceQueue(m_device, indices.graphics_family.value(), 0, &m_graphics_queue);
    vkGetDeviceQueue(m_device, indices.present_family.value(), 0, &m_present_queue);
}

void App::loop()
{
    while (!glfwWindowShouldClose(m_window))
        glfwPollEvents();
}

}
