#include "renderer.hpp"

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include "GLFW/glfw3native.h"
#include "imgui.h"
#include "imgui_impl_bgfx.hpp"
#include "imgui_impl_glfw.h"

Renderer::Renderer(GLFWwindow *window, int width, int height)
    : width(width), height(height) {
  bgfx::renderFrame();

  bgfx::Init init;
  init.type = bgfx::RendererType::Metal;
  init.platformData.nwh = glfwGetCocoaWindow(window);
  init.resolution.width = width;
  init.resolution.height = height;
  init.resolution.reset = BGFX_RESET_VSYNC;
  init.debug = true;

  if (!bgfx::init(init)) {
    std::cerr << "Failed to initialize BGFX!" << std::endl;
  } else {
    std::cout << "BGFX initialized successfully!" << std::endl;
  }

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x202020ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, width, height);

  ImGui::CreateContext();

  ImGui_Implbgfx_Init(255);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
}

Renderer::~Renderer() { bgfx::shutdown(); }

void Renderer::renderFrame() {

  ImGui_Implbgfx_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  ImGui::NewFrame();
  ImGui::ShowDemoWindow();
  ImGui::Render();
  ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

  bgfx::touch(0);
  bgfx::frame();
}
