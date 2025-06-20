#include "gui.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <stdexcept>

Gui *Gui::instance = nullptr;

Gui::Gui(GLFWwindow *window) : window(window) {
  ImGui::CreateContext();
  ImGui_Implbgfx_Init(255);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
}

Gui *Gui::getInstance(GLFWwindow *window) {
  if (instance == nullptr) {
    if (window == nullptr) {
      throw std::runtime_error("Window required for first GUI initialization");
    }
    instance = new Gui(window);
  }
  return instance;
}

void Gui::cleanup() {
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
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
  ImGui::SeparatorText("Particle display");
  ImGui::SliderFloat("Particle size", &particleSize, 1.0f, 100.0f);
  ImGui::ColorEdit4("Particle color low", (float *)&particleColorLow);
  ImGui::ColorEdit4("Particle color high", (float *)&particleColorHigh);

  ImGui::SeparatorText("Particle settings");
  ImGui::SliderInt("Number of particles", &numParticles, 1, 10);
  ImGui::InputInt("Random seed", &randomSeed);

  ImGui::SeparatorText("Interaction settings");
  ImGui::SliderFloat("Interaction strength", &mouseStrength, 1, 50);
  ImGui::SliderFloat("Interaction radius", &mouseRadius, 0, 2);

  ImGui::SeparatorText("Simulation settings");
  ImGui::SliderFloat("SPH radius", &radius, 1.0f, 200.0f);
  ImGui::SliderFloat("Pressure multiplier", &pressureMultiplier, 0.01f, 5.0f);
  ImGui::SliderFloat("Target pressure", &targetPressure, 1.0f, 5000.0f);
  ImGui::SliderInt("Gravity OFF/ON", &gravityStatus, 0, 1);
  ImGui::SliderFloat("Gravity", &gravity, 0, 10);

  ImGui::SeparatorText("Simulation controls");
  ImGui::SliderInt("Pause OFF/ON", &pause, 0, 1);
  if (ImGui::Button("Reset")) {
    reset = true;
  } else {
    reset = false;
  }

  ImGui::End();

  ImGui::Render();
  ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
}
