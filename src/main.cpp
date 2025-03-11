#include <GLFW/glfw3.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include "GLFW/glfw3native.h"

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

  bgfx::Init init;
  init.type = bgfx::RendererType::Metal;
  init.platformData.nwh = glfwGetCocoaWindow(window);
  init.resolution.width = 1000;
  init.resolution.height = 800;
  init.resolution.reset = BGFX_RESET_VSYNC;

  if (!bgfx::init(init)) {
    std::cerr << "Failed to initialize BGFX!" << std::endl;
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
