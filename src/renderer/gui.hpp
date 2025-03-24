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
  int numParticles;
  float radius = 1.0f;
};

#endif
