#include "buffers/vertexBuffer.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/window.hpp"

int main() {
  Window window(1280, 720, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 1280, 720);
  Shaders mainShader("src/shaders/shader.vertex.bin",
                     "src/shaders/shader.fragment.bin");

  VertexBuffer screenVBO(0, "screenVBO");

  while (!window.shouldClose()) {
    window.pollEvents();
    mainShader.submitShader(
        mainShader.vbo, mainShader.ibo, mainShader.shaderProgram,
        mainShader.posGenProgram, mainShader.sphProgram,
        mainShader.projectileBuffer, mainShader.pixelsBuffer,
        mainShader.u_numPoints, mainShader.u_radius, mainShader.u_resolution,
        mainShader.projectileCount, mainShader.radius, mainShader.resolution);
    renderer.renderFrame();
  }

  return 0;
}
