#include "uniformBuffer.hpp"

UniformBuffer::UniformBuffer(const char *buffName) {

  if (strcmp(buffName, "u_numPoints") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
    data = {1 * 256, 0, 0, 0};
  }
  if (strcmp(buffName, "u_radius") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
    data = {50, 0, 0, 0};
  }
  if (strcmp(buffName, "u_resolution") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
    data = {800, 800, 0, 0};
  }
}

void UniformBuffer::init() {
  buffer = bgfx::createUniform(uniformName.c_str(), type);
}

void UniformBuffer::bind() { bgfx::setUniform(buffer, &data); }

void UniformBuffer::destroy() { bgfx::destroy(buffer); }

UniformBuffer::~UniformBuffer() { destroy(); }
