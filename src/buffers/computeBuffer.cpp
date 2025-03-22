#include "computeBuffer.hpp"

ComputeBuffer::ComputeBuffer(uint8_t stageInt, const char *buffName,
                             bgfx::Access::Enum access) {

  if (strcmp(buffName, "particleBuffer") == 0) {

    layout.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .end();

    uint32_t projectileCount = 1 * 256;
    uint32_t posBufferStride = layout.getStride();
    size = projectileCount * posBufferStride;

    stage = stageInt;
  }

  if (strcmp(buffName, "pixelsBuffer") == 0) {
    layout.begin().add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float).end();

    uint32_t pixelsCount = 800 * 800;
    uint32_t pixelsStride = layout.getStride();
    size = pixelsCount * pixelsStride;

    stage = stageInt;
  }

  if (strcmp(buffName, "densitiesBuffer") == 0) {
    layout.begin().add(bgfx::Attrib::Color0, 1, bgfx::AttribType::Float).end();

    uint32_t count = 1 * 256;
    uint32_t stride = layout.getStride();
    size = count * stride;

    stage = stageInt;
  }
}

void ComputeBuffer::init() {
  buffer = bgfx::createDynamicVertexBuffer(size, layout,
                                           BGFX_BUFFER_COMPUTE_READ_WRITE);
}

void ComputeBuffer::bind() { bgfx::setBuffer(stage, buffer, access); }

void ComputeBuffer::destroy() { bgfx::destroy(buffer); }

ComputeBuffer::~ComputeBuffer() { destroy(); }
