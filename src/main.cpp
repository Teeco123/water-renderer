#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/window.hpp"

int main() {
  Window window(1200, 800, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 800, 800);
  Shaders mainShader("src/shaders/shader.vertex.bin",
                     "src/shaders/shader.fragment.bin");

  while (!window.shouldClose()) {
    window.pollEvents();
    mainShader.submitShader(mainShader.vbo, mainShader.ibo,
                            mainShader.shaderProgram, mainShader.posGenProgram,
                            mainShader.sphProgram, mainShader.projectileBuffer,
                            mainShader.pixelsBuffer, mainShader.u_numPoints,
                            mainShader.u_radius, mainShader.u_resolution);
    renderer.renderFrame();
  }

  return 0;
}
