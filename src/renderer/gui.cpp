#include "gui.hpp"
#include "imgui.h"

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
  ImGui::SliderFloat("SPH Radius", &radius, 1.0f, 200.0f);
  ImGui::SliderFloat("Particle size", &particleSize, 1.0f, 100.0f);
  ImGui::SliderFloat("Pressure multiplier", &pressureMultiplier, 0.01f, 2.0f);
  ImGui::SliderInt("Number of particles", &numParticles, 1, 10);
  ImGui::ColorEdit4("Particle color", (float *)&particleColor);
  ImGui::InputInt("Random seed", &randomSeed);
  if (ImGui::Button("Reset")) {
    reset = true;
  } else {
    reset = false;
  }

  ImGui::End();

  ImGui::Render();
  ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
}
