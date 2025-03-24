#include "uniformBuffer.hpp"

UniformBuffer::UniformBuffer(const char *buffName) {

  if (strcmp(buffName, "u_numPoints") == 0) {
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
}

void UniformBuffer::init() {
  buffer = bgfx::createUniform(uniformName.c_str(), type);
}

void UniformBuffer::bind() {}

void UniformBuffer::bindUniform(const Gui &gui) {
  if (strcmp(uniformName.c_str(), "u_numPoints") == 0) {
    data = {(float)gui.numParticles * 256, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_radius") == 0) {
    data = {gui.radius, 0, 0, 0};
  }
  if (strcmp(uniformName.c_str(), "u_resolution") == 0) {
    data = {2000, 2000, 0, 0};
  }
  bgfx::setUniform(buffer, &data);
}

void UniformBuffer::destroy() { bgfx::destroy(buffer); }

UniformBuffer::~UniformBuffer() { destroy(); }
