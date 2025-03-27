#ifndef GUI_HPP
#define GUI_HPP

#include "../utils/types.hpp"
#include "imgui.h"
#include "imgui_impl_bgfx.hpp"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

class Gui {
public:
  Gui(GLFWwindow *window);
  ~Gui();

  void render();

  int resX, resY;
  int numParticles = 3;
  float radius = 1.0f;
  float particleSize = 1.0f;
  float pressureMultiplier = 0.01f;
  float targetPressure = 1.0f;
  Vec4 particleColorLow = {0, 0, 1, 1};
  Vec4 particleColorHigh = {1, 0, 0, 1};
  int gravityStatus = 0;
  int randomSeed = 1;

  int pause = 0;
  bool reset = false;
};

#endif
