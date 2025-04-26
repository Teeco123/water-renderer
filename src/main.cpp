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
  UniformBuffer u_gravityStatus;
  UniformBuffer u_gravity;
  UniformBuffer u_resolution;
  UniformBuffer u_randomSeed;
  UniformBuffer u_mouse;
  UniformBuffer u_mouseStrength;
  UniformBuffer u_mouseRadius;
  UniformBuffer u_numPoints;
  UniformBuffer u_radius;
  UniformBuffer u_pressureMultiplier;
  UniformBuffer u_targetPressure;
  UniformBuffer u_particleSize;
  UniformBuffer u_particleColorLow;
  UniformBuffer u_particleColorHigh;

  ComputeBuffer particleBuffer;
  ComputeBuffer densitiesBuffer;
  ComputeBuffer velocitiesBuffer;
  ComputeBuffer predictionsBuffer;

  ComputeProgram posGenProgram;
  ComputeProgram step1Program;
  ComputeProgram step2Program;
  ComputeProgram step3Program;
  ComputeProgram step4Program;

  SimulationData(int numParticles)
      : u_gravityStatus("u_gravityStatus"), u_gravity("u_gravity"),
        u_resolution("u_resolution"), u_randomSeed("u_randomSeed"),
        u_mouse("u_mouse"), u_mouseStrength("u_mouseStrength"),
        u_mouseRadius("u_mouseRadius"), u_numPoints("u_numParticles"),
        u_radius("u_radius"), u_pressureMultiplier("u_pressureMultiplier"),
        u_targetPressure("u_targetPressure"), u_particleSize("u_particleSize"),
        u_particleColorLow("u_particleColorLow"),
        u_particleColorHigh("u_particleColorHigh"),

        particleBuffer(0, "particleBuffer", bgfx::Access::ReadWrite),
        densitiesBuffer(2, "densitiesBuffer", bgfx::Access::ReadWrite),
        velocitiesBuffer(3, "velocitiesBuffer", bgfx::Access::ReadWrite),
        predictionsBuffer(4, "predictionsBuffer", bgfx::Access::ReadWrite),
        posGenProgram("src/shaders/posGen.compute.bin", numParticles, 1, 1),
        step1Program("src/shaders/step1.compute.bin", numParticles, 1, 1),
        step2Program("src/shaders/step2.compute.bin", numParticles, 1, 1),
        step3Program("src/shaders/step3.compute.bin", numParticles, 1, 1),
        step4Program("src/shaders/step4.compute.bin", numParticles, 1, 1) {}
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
    sim.u_gravity.bindUniform(gui);
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

  ShaderProgram shaderProgram("src/shaders/shader.vertex.bin",
                              "src/shaders/shader.fragment.bin");

  SimulationData sim(gui.numParticles);

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
    sim.u_numPoints.bindUniform(gui);
    sim.u_radius.bindUniform(gui);
    sim.u_resolution.bindUniform(gui);
    sim.u_particleSize.bindUniform(gui);
    sim.u_pressureMultiplier.bindUniform(gui);
    sim.u_particleColorLow.bindUniform(gui);
    sim.u_particleColorHigh.bindUniform(gui);
    sim.particleBuffer.bind();
    sim.velocitiesBuffer.bind();
    shaderProgram.submit();

    gui.render();

    renderer.renderFrame();
  }

  return 0;
}
