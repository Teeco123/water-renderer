#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <iostream>

void error_callback(int error, const char *description) {
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // Use Metal API
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE); // Optional

  // Create GLFW window
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Water renderer", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
    return -1;
  }

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
