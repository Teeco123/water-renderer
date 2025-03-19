#ifndef COMPUTE_BUFFER_HPP
#define COMPUTE_BUFFER_HPP

#include "baseBuffer.hpp"

class ComputeBuffer : public BaseBuffer {
private:
  bgfx::VertexLayout layout;
  bgfx::DynamicVertexBufferHandle buffer;
  bgfx::Access::Enum access;
  const bgfx::Memory *size;
  uint8_t stage;

public:
  ComputeBuffer(uint8_t stageInt, const char *buffName,
                bgfx::Access::Enum access);
  void init() override;
  void bind() override;
  void destroy() override;

  bgfx::DynamicVertexBufferHandle Get() const;

  ~ComputeBuffer();
};

#endif
