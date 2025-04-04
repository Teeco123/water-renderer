#include "indexBuffer.hpp"
#include "bgfx/bgfx.h"

IndexBuffer::IndexBuffer(const char *buffName) {

  if (strcmp(buffName, "screenIBO") == 0) {
    uint16_t squareIndices[] = {
        0, 2, 1, // First triangle
        1, 2, 3  // Second triangle
    };

    data = bgfx::copy(squareIndices, sizeof(squareIndices));
  }
  ibo = bgfx::createIndexBuffer(data);
}

void IndexBuffer::bind() { bgfx::setIndexBuffer(ibo); }

void IndexBuffer::destroy() { bgfx::destroy(ibo); }

IndexBuffer::~IndexBuffer() { destroy(); }
