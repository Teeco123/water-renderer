#pragma once

#include "../utils/types.hpp"
#include "imgui_impl_bgfx.h"
#include <GLFW/glfw3.h>

class Gui {
public:
  Gui(const Gui &) = delete;
  Gui &operator=(const Gui &) = delete;

  static Gui *getInstance(GLFWwindow *window = nullptr);
  static void cleanup();
  void render();
  ~Gui();

  int resX, resY;
  int numParticles = 3;
  float radius = 1.0f;
  float particleSize = 1.0f;
  float pressureMultiplier = 0.01f;
  float targetPressure = 1.0f;
  Vec4 particleColorLow = {0, 0, 1, 1};
  Vec4 particleColorHigh = {1, 0, 0, 1};
  int gravityStatus = 0;
  float gravity = 1;
  int randomSeed = 1;

  double mousePosX;
  double mousePosY;
  int mouseButton = 0;
  float mouseStrength = 1;
  float mouseRadius = 0;

  int pause = 0;
  bool reset = false;

private:
  static Gui *instance;
  GLFWwindow *window;
  Gui(GLFWwindow *window);
};
