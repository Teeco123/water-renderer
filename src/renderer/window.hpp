#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  static Window *getInstance(int width, int height, const char *title);
  static void cleanup();
  ~Window();

  bool shouldClose() const;
  void pollEvents();
  GLFWwindow *getNativeWindow() const;

private:
  static Window *instance;
  GLFWwindow *window;
  Window(int width, int height, const char *title);
};
