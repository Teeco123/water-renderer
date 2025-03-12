#include "Window.hpp"
#include <iostream>

Window::Window(int width, int height, const char *title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    window = nullptr;
    return;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
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
