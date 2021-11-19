#define PROJECT_NAME "hummingbird"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

class App {
public:
    void run() {
        mainLoop();
    }

    App() {
        initWindow();
        initVulkan();
    }

    ~App() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

private:
    GLFWwindow* m_window;

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_window = glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
    }

    void initVulkan() {

    }

    void mainLoop() {
        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();
        }
    }
};

int main() {
    App app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}