#include "gui.hpp"

#include "imgui.h"
#include "imgui_impl_bgfx.hpp"
#include "imgui_impl_glfw.h"

Gui::Gui(GLFWwindow *window) {
  ImGui::CreateContext();
  ImGui_Implbgfx_Init(255);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
}

Gui::~Gui() {
  ImGui_Implbgfx_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Gui::render() {
  ImGui_Implbgfx_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  ImGui::NewFrame();

  ImGui::Begin("Settings", 0,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  ImGui::End();

  ImGui::Render();
  ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
}
