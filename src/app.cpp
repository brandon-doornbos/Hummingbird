#include <stdexcept>

#include "app.hpp"

void App::run()
{
    mainLoop();
}

App::App(AppInfo app_info)
    : m_app_info(app_info)
{
    initWindow();
    initVulkan();
}

App::~App()
{
    vkDestroyInstance(m_instance, nullptr);

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::initWindow()
{
    if (glfwInit() != GLFW_TRUE)
        throw std::runtime_error("Failed to initialize GLFW.");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_app_info.width, m_app_info.height, m_app_info.name, nullptr, nullptr);
    if (m_window == NULL)
        throw std::runtime_error("Failed to create a window.");
}

void App::createInstance()
{
    // VkApplicationInfo vkAppInfo{};
    // vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // vkAppInfo.pApplicationName = m_app_info.name;
    // vkAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    // vkAppInfo.pEngineName = "No Engine";
    // vkAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    // vkAppInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    if (glfwExtensions == NULL)
        throw std::runtime_error("Failed to get required extensions.");

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
        throw std::runtime_error("failed to create instance!");

    // https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance
    // Checking for extension support
}

void App::initVulkan()
{
    createInstance();
}

void App::mainLoop()
{
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
    }
}