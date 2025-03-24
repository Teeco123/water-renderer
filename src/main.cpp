#include "buffers/computeBuffer.hpp"
#include "buffers/indexBuffer.hpp"
#include "buffers/uniformBuffer.hpp"
#include "buffers/vertexBuffer.hpp"
#include "programs/computeProgram.hpp"
#include "programs/shaderProgram.hpp"
#include "renderer/gui.hpp"
#include "renderer/renderer.hpp"
#include "renderer/window.hpp"

int main() {
  Window window(1000, 1000, "Water Renderer");
  Renderer renderer(window.getNativeWindow(), 2000, 2000);
  Gui gui(window.getNativeWindow());

  VertexBuffer vbo(0, "screenVBO");
  IndexBuffer ibo("screenIBO");

  ComputeBuffer particleBuffer(0, "particleBuffer", bgfx::Access::ReadWrite);
  ComputeBuffer pixelsBuffer(1, "pixelsBuffer", bgfx::Access::ReadWrite);
  ComputeBuffer densitiesBuffer(2, "densitiesBuffer", bgfx::Access::ReadWrite);
  ComputeBuffer velocitiesBuffer(3, "velocitiesBuffer",
                                 bgfx::Access::ReadWrite);

  UniformBuffer u_numPoints("u_numPoints");
  UniformBuffer u_radius("u_radius");
  UniformBuffer u_resolution("u_resolution");

  ShaderProgram shaderProgram("src/shaders/shader.vertex.bin",
                              "src/shaders/shader.fragment.bin");

  ComputeProgram posGenProgram("src/shaders/posGen.compute.bin", 2, 1, 1);
  ComputeProgram step1Program("src/shaders/step1.compute.bin", 2, 1, 1);
  ComputeProgram step2Program("src/shaders/step2.compute.bin", 2, 1, 1);
  ComputeProgram step3Program("src/shaders/step3.compute.bin", 2, 1, 1);

  //------------------------------------------------------------------------------------
  // Init everything
  vbo.init();
  ibo.init();
  particleBuffer.init();
  pixelsBuffer.init();
  densitiesBuffer.init();
  velocitiesBuffer.init();
  u_numPoints.init();
  u_radius.init();
  u_resolution.init();
  shaderProgram.init();
  posGenProgram.init();
  step1Program.init();
  step2Program.init();
  step3Program.init();

  //------------------------------------------------------------------------------------
  // Generate positions of particles
  u_numPoints.bind();
  u_radius.bind();
  u_resolution.bind();
  particleBuffer.bind();
  posGenProgram.submit();

  while (!window.shouldClose()) {
    window.pollEvents();

    gui.render();

    //------------------------------------------------------------------------------------
    // Calculate cached densities of particle positions
    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    particleBuffer.bind();
    densitiesBuffer.bind();
    velocitiesBuffer.bind();
    step1Program.submit();

    //------------------------------------------------------------------------------------
    // Calculate velocity based on pressure force of particle
    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    particleBuffer.bind();
    densitiesBuffer.bind();
    velocitiesBuffer.bind();
    step2Program.submit();

    //------------------------------------------------------------------------------------
    // Update positions and handle boundaries colistions
    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    particleBuffer.bind();
    densitiesBuffer.bind();
    velocitiesBuffer.bind();
    step3Program.submit();

    vbo.bind();
    ibo.bind();
    u_numPoints.bind();
    u_radius.bind();
    u_resolution.bind();
    particleBuffer.bind();
    pixelsBuffer.bind();
    shaderProgram.submit();

    renderer.renderFrame();
  }

  return 0;
}
