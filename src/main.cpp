#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/window.hpp"

int main() {
  Window window(1000, 800, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 1000, 800);
  Shaders mainShader("src/shaders/vs.sc.bin", "src/shaders/fs.sc.bin");

  while (!window.shouldClose()) {
    window.pollEvents();
    mainShader.submitShader(mainShader.vbo, mainShader.ibo,
                            mainShader.shaderProgram);
    renderer.renderFrame();
  }

  return 0;
}
