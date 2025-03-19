#include "uniformBuffer.hpp"

UniformBuffer::UniformBuffer(const char *buffName) {

  if (strcmp(buffName, "u_radius") == 0) {
    uniformName = buffName;
    type = bgfx::UniformType::Vec4;
    data = {10, 0, 0, 0};
  }
}

void UniformBuffer::init() {
  buffer = bgfx::createUniform(uniformName.c_str(), type);
}

void UniformBuffer::bind() { bgfx::setUniform(buffer, &data); }

void UniformBuffer::destroy() { bgfx::destroy(buffer); }

UniformBuffer::~UniformBuffer() { destroy(); }
