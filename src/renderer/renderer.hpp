#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <iostream>

class Renderer {
public:
  Renderer(GLFWwindow *window, int width, int height);
  ~Renderer();

  void renderFrame();

private:
  int width, height;
};

#endif
