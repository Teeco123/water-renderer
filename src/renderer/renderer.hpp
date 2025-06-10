#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/bx.h>
#include <iostream>

class Renderer {
public:
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  static Renderer *getInstance(GLFWwindow *window, int width, int height);
  static void cleanup();
  ~Renderer();

  void renderFrame();

private:
  static Renderer *instance;
  int width, height;
  Renderer(GLFWwindow *window, int width, int height);
};

#endif
