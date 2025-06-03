#include "window.hpp"

Window *Window::instance = nullptr;

Window::Window(int width, int height, const char *title) {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    window = nullptr;
    return;
  }

  // Non resizable window
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Try creating window
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
  }
}

Window *Window::getInstance(int width, int height, const char *title) {
  if (instance == nullptr) {
    instance = new Window(width, height, title);
  }
  return instance;
}

void Window::cleanup() {
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

Window::~Window() {
  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::pollEvents() { glfwPollEvents(); }

GLFWwindow *Window::getNativeWindow() const { return window; }
