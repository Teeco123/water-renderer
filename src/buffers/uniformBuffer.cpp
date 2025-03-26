#include "uniformBuffer.hpp"

UniformBuffer::UniformBuffer(const char *buffName) {

  if (strcmp(buffName, "u_numParticles") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_radius") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_resolution") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_particleSize") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_randomSeed") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_pressureMultiplier") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_particleColor") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_targetPressure") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }
  if (strcmp(buffName, "u_gravityStatus") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
  }

  buffer = bgfx::createUniform(uniformName.c_str(), type);
}

void UniformBuffer::bind() {}

void UniformBuffer::bindUniform(const Gui &gui) {
  if (strcmp(uniformName.c_str(), "u_numParticles") == 0) {
    data = {(float)gui.numParticles * 256, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_radius") == 0) {
    data = {gui.radius, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_resolution") == 0) {
    data = {2000, 2000, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_particleSize") == 0) {
    data = {gui.particleSize, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_randomSeed") == 0) {
    data = {(float)gui.randomSeed, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_pressureMultiplier") == 0) {
    data = {gui.pressureMultiplier, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_particleColor") == 0) {
    data = {gui.particleColor.x, gui.particleColor.y, gui.particleColor.z,
            gui.particleColor.w};
  }
  if (strcmp(uniformName.c_str(), "u_targetPressure") == 0) {
    data = {gui.targetPressure, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_gravityStatus") == 0) {
    data = {(float)gui.gravityStatus, 0, 0, 0};
  }
  bgfx::setUniform(buffer, &data);
}

void UniformBuffer::destroy() { bgfx::destroy(buffer); }

UniformBuffer::~UniformBuffer() { destroy(); }
