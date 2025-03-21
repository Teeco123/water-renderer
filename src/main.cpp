#include "buffers/computeBuffer.hpp"
#include "buffers/indexBuffer.hpp"
#include "buffers/uniformBuffer.hpp"
#include "buffers/vertexBuffer.hpp"
#include "programs/computeProgram.hpp"
#include "programs/shaderProgram.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/window.hpp"

int main() {
  Window window(800, 800, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 800, 800);

  VertexBuffer vbo(0, "screenVBO");
  IndexBuffer ibo("screenIBO");

  ComputeBuffer projectileBuffer(0, "projectileBuffer",
                                 bgfx::Access::ReadWrite);
  ComputeBuffer pixelsBuffer(1, "pixelsBuffer", bgfx::Access::ReadWrite);

  UniformBuffer u_numPoints("u_numPoints");
  UniformBuffer u_radius("u_radius");
  UniformBuffer u_resolution("u_resolution");

  ShaderProgram shaderProgram("src/shaders/shader.vertex.bin",
                              "src/shaders/shader.fragment.bin");

  ComputeProgram posGenProgram("src/shaders/posGen.compute.bin", 256 / 256, 1,
                               1);
  ComputeProgram sphProgram("src/shaders/sph.compute.bin", 800 / 16, 800 / 16,
                            1);

  // Inits
  vbo.init();
  ibo.init();
  projectileBuffer.init();
  pixelsBuffer.init();
  u_numPoints.init();
  u_radius.init();
  u_resolution.init();
  shaderProgram.init();
  posGenProgram.init();
  sphProgram.init();

  while (!window.shouldClose()) {
    window.pollEvents();

    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    projectileBuffer.bind();
    posGenProgram.submit();

    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    projectileBuffer.bind();
    pixelsBuffer.bind();
    sphProgram.submit();

    vbo.bind();
    ibo.bind();
    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    projectileBuffer.bind();
    pixelsBuffer.bind();
    shaderProgram.submit();

    renderer.renderFrame();
  }

  return 0;
}
