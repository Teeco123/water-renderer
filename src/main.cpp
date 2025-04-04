#include "GLFW/glfw3.h"
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
  ComputeBuffer densitiesBuffer(2, "densitiesBuffer", bgfx::Access::ReadWrite);
  ComputeBuffer velocitiesBuffer(3, "velocitiesBuffer",
                                 bgfx::Access::ReadWrite);
  ComputeBuffer predictionsBuffer(4, "predictionsBuffer",
                                  bgfx::Access::ReadWrite);

  UniformBuffer u_numPoints("u_numParticles");
  UniformBuffer u_radius("u_radius");
  UniformBuffer u_resolution("u_resolution");
  UniformBuffer u_particleSize("u_particleSize");
  UniformBuffer u_randomSeed("u_randomSeed");
  UniformBuffer u_pressureMultiplier("u_pressureMultiplier");
  UniformBuffer u_particleColorLow("u_particleColorLow");
  UniformBuffer u_particleColorHigh("u_particleColorHigh");
  UniformBuffer u_targetPressure("u_targetPressure");
  UniformBuffer u_gravityStatus("u_gravityStatus");
  UniformBuffer u_mouse("u_mouse");
  UniformBuffer u_mouseStrength("u_mouseStrength");
  UniformBuffer u_mouseRadius("u_mouseRadius");

  ShaderProgram shaderProgram("src/shaders/shader.vertex.bin",
                              "src/shaders/shader.fragment.bin");

  ComputeProgram posGenProgram("src/shaders/posGen.compute.bin",
                               gui.numParticles, 1, 1);
  ComputeProgram step1Program("src/shaders/step1.compute.bin", gui.numParticles,
                              1, 1);
  ComputeProgram step2Program("src/shaders/step2.compute.bin", gui.numParticles,
                              1, 1);
  ComputeProgram step3Program("src/shaders/step3.compute.bin", gui.numParticles,
                              1, 1);
  ComputeProgram step4Program("src/shaders/step4.compute.bin", gui.numParticles,
                              1, 1);

  //------------------------------------------------------------------------------------
  // Generate positions of particles
  u_numPoints.bindUniform(gui);
  u_radius.bindUniform(gui);
  u_resolution.bindUniform(gui);
  u_randomSeed.bindUniform(gui);
  particleBuffer.bind();
  densitiesBuffer.bind();
  velocitiesBuffer.bind();
  posGenProgram.submit();

  while (!window.shouldClose()) {
    window.pollEvents();

    glfwGetCursorPos(window.getNativeWindow(), &gui.mousePosX, &gui.mousePosY);

    int leftMouse =
        glfwGetMouseButton(window.getNativeWindow(), GLFW_MOUSE_BUTTON_LEFT);
    int rightMouse =
        glfwGetMouseButton(window.getNativeWindow(), GLFW_MOUSE_BUTTON_RIGHT);

    if (leftMouse == GLFW_PRESS) {
      gui.mouseButton = 1;
    } else if (rightMouse == GLFW_PRESS) {
      gui.mouseButton = 2;
    } else {
      gui.mouseButton = 0;
    }

    //------------------------------------------------------------------------------------
    // Re-generate positions of particles
    if (gui.reset) {
      u_numPoints.bindUniform(gui);
      u_radius.bindUniform(gui);
      u_resolution.bindUniform(gui);
      u_randomSeed.bindUniform(gui);
      particleBuffer.bind();
      densitiesBuffer.bind();
      velocitiesBuffer.bind();
      posGenProgram.submit();
    }

    if (gui.pause == 0) {
      u_gravityStatus.bindUniform(gui);
      u_resolution.bindUniform(gui);
      u_mouse.bindUniform(gui);
      u_mouseStrength.bindUniform(gui);
      u_mouseRadius.bindUniform(gui);
      particleBuffer.bind();
      velocitiesBuffer.bind();
      predictionsBuffer.bind();
      step1Program.submit();

      //------------------------------------------------------------------------------------
      // Calculate cached densities of particle positions
      u_numPoints.bindUniform(gui);
      u_radius.bindUniform(gui);
      u_resolution.bindUniform(gui);
      particleBuffer.bind();
      densitiesBuffer.bind();
      velocitiesBuffer.bind();
      predictionsBuffer.bind();
      step2Program.submit();

      //------------------------------------------------------------------------------------
      // Calculate velocity based on pressure force of particle
      u_numPoints.bindUniform(gui);
      u_radius.bindUniform(gui);
      u_resolution.bindUniform(gui);
      u_pressureMultiplier.bindUniform(gui);
      u_targetPressure.bindUniform(gui);
      particleBuffer.bind();
      densitiesBuffer.bind();
      velocitiesBuffer.bind();
      predictionsBuffer.bind();
      step3Program.submit();

      //------------------------------------------------------------------------------------
      // Update positions and handle boundaries colistions
      u_numPoints.bindUniform(gui);
      u_radius.bindUniform(gui);
      u_resolution.bindUniform(gui);
      particleBuffer.bind();
      densitiesBuffer.bind();
      velocitiesBuffer.bind();
      predictionsBuffer.bind();
      step4Program.submit();
    }

    vbo.bind();
    ibo.bind();
    u_numPoints.bindUniform(gui);
    u_radius.bindUniform(gui);
    u_resolution.bindUniform(gui);
    u_particleSize.bindUniform(gui);
    u_pressureMultiplier.bindUniform(gui);
    u_particleColorLow.bindUniform(gui);
    u_particleColorHigh.bindUniform(gui);
    particleBuffer.bind();
    velocitiesBuffer.bind();
    shaderProgram.submit();

    gui.render();

    renderer.renderFrame();
  }

  return 0;
}
