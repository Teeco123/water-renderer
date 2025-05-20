#include "renderer.hpp"

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_WAYLAND
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif

#include "GLFW/glfw3native.h"

static void *glfwNativeWindowHandle(GLFWwindow *_window) {
#if BX_PLATFORM_LINUX
  if (GLFW_PLATFORM_WAYLAND == glfwGetPlatform()) {
    return glfwGetWaylandWindow(_window);
  }

  return (void *)uintptr_t(glfwGetX11Window(_window));
#elif BX_PLATFORM_OSX
  return glfwGetCocoaWindow(_window);
#elif BX_PLATFORM_WINDOWS
  return glfwGetWin32Window(_window);
#endif // BX_PLATFORM_
}

static bgfx::RendererType::Enum glfwNativeRendererType() {
#if BX_PLATFORM_LINUX
  return bgfx::RendererType::Vulkan;
#elif BX_PLATFORM_OSX
  return bgfx::RendererType::Metal;
#elif BX_PLATFORM_WINDOWS
  return bgfx::RendererType::Direct3D12;
#endif
}

Renderer::Renderer(GLFWwindow *window, int width, int height)
    : width(width), height(height) {
  bgfx::renderFrame();

  // Create metal renderer
  bgfx::Init init;
  init.type = glfwNativeRendererType();
  init.platformData.nwh = glfwNativeWindowHandle(window);
  init.resolution.width = width;
  init.resolution.height = height;
  init.resolution.reset = BGFX_RESET_VSYNC;
  init.debug = true;

  // Try to initialize BGFX
  if (!bgfx::init(init)) {
    std::cerr << "Failed to initialize BGFX!" << std::endl;
  } else {
    std::cout << "BGFX initialized successfully!" << std::endl;
  }

  // Set color and size of renderer
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x202020ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, width, height);
}

Renderer::~Renderer() { bgfx::shutdown(); }

void Renderer::renderFrame() {
  // Clear frame before rendering frame
  bgfx::touch(0);
  bgfx::frame();
}
