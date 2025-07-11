#include "uniformBuffer.hpp"

UniformBuffer::UniformBuffer(const char *buffName)
    : uniformName(buffName), type(bgfx::UniformType::Vec4) {
  buffer = bgfx::createUniform(uniformName.c_str(), type);
}

void UniformBuffer::bind() {}

void UniformBuffer::bindUniform(const Gui *gui) {
  if (strcmp(uniformName.c_str(), "u_numParticles") == 0) {
    data = {(float)gui->numParticles * 256, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_radius") == 0) {
    data = {gui->radius, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_resolution") == 0) {
    data = {2000, 2000, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_particleSize") == 0) {
    data = {gui->particleSize, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_randomSeed") == 0) {
    data = {(float)gui->randomSeed, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_pressureMultiplier") == 0) {
    data = {gui->pressureMultiplier, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_particleColorLow") == 0) {
    data = {gui->particleColorLow.x, gui->particleColorLow.y,
            gui->particleColorLow.z, gui->particleColorLow.w};
  }
  if (strcmp(uniformName.c_str(), "u_particleColorHigh") == 0) {
    data = {gui->particleColorHigh.x, gui->particleColorHigh.y,
            gui->particleColorHigh.z, gui->particleColorHigh.w};
  }
  if (strcmp(uniformName.c_str(), "u_targetPressure") == 0) {
    data = {gui->targetPressure, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_gravityStatus") == 0) {
    data = {(float)gui->gravityStatus, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_gravity") == 0) {
    data = {gui->gravity, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_mouse") == 0) {
    data = {(float)gui->mousePosX * 2, (float)gui->mousePosY * 2,
            (float)gui->mouseButton, 0};
  }
  if (strcmp(uniformName.c_str(), "u_mouseStrength") == 0) {
    data = {gui->mouseStrength, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_mouseRadius") == 0) {
    data = {gui->mouseRadius, 0, 0, 0};
  }
  bgfx::setUniform(buffer, &data);
}

void UniformBuffer::destroy() { bgfx::destroy(buffer); }

UniformBuffer::~UniformBuffer() { destroy(); }
