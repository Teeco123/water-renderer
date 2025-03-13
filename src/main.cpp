#include "renderer/Renderer.hpp"
#include "renderer/Window.hpp"
#include "renderer/shaders.hpp"

int main() {
  Window window(1000, 800, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 1000, 800);
  Shaders shaders;

  while (!window.shouldClose()) {
    window.pollEvents();
    shaders.submitShader(shaders.vbo, shaders.ibo, shaders.shaderProgram);
    renderer.renderFrame();
  }

  return 0;
}
