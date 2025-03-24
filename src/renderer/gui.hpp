#ifndef GUI_HPP
#define GUI_HPP

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
  bool reset = false;
};

#endif
