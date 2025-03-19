#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include "baseBuffer.hpp"
#include "bgfx/bgfx.h"

class IndexBuffer : public BaseBuffer {
private:
  bgfx::IndexBufferHandle ibo;
  const bgfx::Memory *data;

public:
  IndexBuffer(const char *buffName);
  void init() override;
  void bind() override;
  void destroy() override;

  bgfx::IndexBufferHandle Get() const;

  ~IndexBuffer();
};

#endif
