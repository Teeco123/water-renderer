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

struct SimulationData {
  UniformBuffer &u_gravityStatus;
  UniformBuffer &u_resolution;
  UniformBuffer &u_randomSeed;
  UniformBuffer &u_mouse;
  UniformBuffer &u_mouseStrength;
  UniformBuffer &u_mouseRadius;
  UniformBuffer &u_numPoints;
  UniformBuffer &u_radius;
  UniformBuffer &u_pressureMultiplier;
  UniformBuffer &u_targetPressure;

  ComputeBuffer &particleBuffer;
  ComputeBuffer &densitiesBuffer;
  ComputeBuffer &velocitiesBuffer;
  ComputeBuffer &predictionsBuffer;

  ComputeProgram &posGenProgram;
  ComputeProgram &step1Program;
  ComputeProgram &step2Program;
  ComputeProgram &step3Program;
  ComputeProgram &step4Program;
};

void reset(Gui &gui, SimulationData &sim) {
  sim.u_numPoints.bindUniform(gui);
  sim.u_radius.bindUniform(gui);
  sim.u_resolution.bindUniform(gui);
  sim.u_randomSeed.bindUniform(gui);
  sim.particleBuffer.bind();
  sim.densitiesBuffer.bind();
  sim.velocitiesBuffer.bind();
  sim.posGenProgram.submit();
}

void step(int pause, Gui &gui, SimulationData &sim) {
  if (pause != 1) {
    sim.u_gravityStatus.bindUniform(gui);
    sim.u_resolution.bindUniform(gui);
    sim.u_mouse.bindUniform(gui);
    sim.u_mouseStrength.bindUniform(gui);
    sim.u_mouseRadius.bindUniform(gui);

    sim.particleBuffer.bind();
    sim.velocitiesBuffer.bind();
    sim.predictionsBuffer.bind();
    sim.step1Program.submit();

    sim.u_numPoints.bindUniform(gui);
    sim.u_radius.bindUniform(gui);
    sim.u_resolution.bindUniform(gui);
    sim.particleBuffer.bind();
    sim.densitiesBuffer.bind();
    sim.velocitiesBuffer.bind();
    sim.predictionsBuffer.bind();
    sim.step2Program.submit();

    sim.u_numPoints.bindUniform(gui);
    sim.u_radius.bindUniform(gui);
    sim.u_resolution.bindUniform(gui);
    sim.u_pressureMultiplier.bindUniform(gui);
    sim.u_targetPressure.bindUniform(gui);
    sim.particleBuffer.bind();
    sim.densitiesBuffer.bind();
    sim.velocitiesBuffer.bind();
    sim.predictionsBuffer.bind();
    sim.step3Program.submit();

    sim.u_numPoints.bindUniform(gui);
    sim.u_radius.bindUniform(gui);
    sim.u_resolution.bindUniform(gui);
    sim.particleBuffer.bind();
    sim.densitiesBuffer.bind();
    sim.velocitiesBuffer.bind();
    sim.predictionsBuffer.bind();
    sim.step4Program.submit();
  }
}

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

  SimulationData sim = {
      u_gravityStatus,      u_resolution,      u_randomSeed,   u_mouse,
      u_mouseStrength,      u_mouseRadius,     u_numPoints,    u_radius,
      u_pressureMultiplier, u_targetPressure,  particleBuffer, densitiesBuffer,
      velocitiesBuffer,     predictionsBuffer, posGenProgram,  step1Program,
      step2Program,         step3Program,      step4Program};

  reset(gui, sim);

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

    if (gui.reset) {
      reset(gui, sim);
    }

    step(gui.pause, gui, sim);
    step(gui.pause, gui, sim);
    step(gui.pause, gui, sim);
    step(gui.pause, gui, sim);
    step(gui.pause, gui, sim);

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
