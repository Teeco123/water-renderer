#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "baseBuffer.hpp"
#include "bgfx/bgfx.h"

class VertexBuffer : public BaseBuffer {
private:
  bgfx::VertexLayout layout;
  bgfx::VertexBufferHandle vbo;
  const bgfx::Memory *data;
  uint8_t stream;

public:
  VertexBuffer(uint8_t streamInt, const char *buffName);
  void init() override;
  void bind() override;
  void destroy() override;

  bgfx::VertexBufferHandle Get() const;

  ~VertexBuffer();
};

#endif
