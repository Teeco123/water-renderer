#ifndef COMPUTE_BUFFER_HPP
#define COMPUTE_BUFFER_HPP

#include <bgfx/bgfx.h>
#include <string.h>

class ComputeBuffer {
public:
  ComputeBuffer(uint8_t stageInt, const char *buffName,
                bgfx::Access::Enum access);
  void bind();
  void destroy();
  bgfx::DynamicVertexBufferHandle GetHandle() const;
  ~ComputeBuffer();

private:
  bgfx::VertexLayout layout;
  bgfx::DynamicVertexBufferHandle buffer;
  bgfx::Access::Enum access;
  uint32_t size;
  uint8_t stage;
};

#endif
