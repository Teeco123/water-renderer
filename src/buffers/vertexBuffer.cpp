#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(uint8_t streamInt, const char *buffName) {

  if (strcmp(buffName, "screenVBO") == 0) {
    Vec2 squareVertices[] = {
        {-1.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, -1.0f}, {1.0f, -1.0f}};

    layout.begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .end();

    data = bgfx::makeRef(squareVertices, sizeof(squareVertices));
    stream = streamInt;
  }
}

void VertexBuffer::init() { vbo = bgfx::createVertexBuffer(data, layout); }

void VertexBuffer::bind() { bgfx::setVertexBuffer(stream, vbo); }

void VertexBuffer::destroy() { bgfx::destroy(vbo); }

VertexBuffer::~VertexBuffer() { destroy(); }
