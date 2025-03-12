
#include "renderer/Renderer.hpp"
#include "renderer/Window.hpp"

int main() {
  Window window(1000, 800, "Water Renderer");
  if (!window.getNativeWindow())
    return -1;

  Renderer renderer(window.getNativeWindow(), 1000, 800);

  while (!window.shouldClose()) {
    window.pollEvents();
    renderer.renderFrame();
  }

  return 0;
}
