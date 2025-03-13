#include "bgfx/bgfx.h"
#include "bx/file.h"
#include "bx/readerwriter.h"
#include "renderer/Renderer.hpp"
#include "renderer/Window.hpp"
#include <cstdio>

const bgfx::Memory *loadShader(const char *filename) {
  bx::FileReader fileReader;
  if (!bx::open(&fileReader, filename)) {
    printf("Failed to open shader file: %s\n", filename);
    return nullptr;
  }

  // Get file size
  bx::Error err;
  uint32_t size = (uint32_t)bx::getSize(&fileReader);

  // Allocate memory for shader
  const bgfx::Memory *mem = bgfx::alloc(size + 1);

  // Read file content into memory
  bx::read(&fileReader, mem->data, size, &err);

  // Null-terminate for safety
  mem->data[size] = '\0';

  bx::close(&fileReader);
  return mem;
}

int main() {
  Window window(1000, 800, "Water Renderer");
  if (!window.getNativeWindow())
    return -1;

  Renderer renderer(window.getNativeWindow(), 1000, 800);

  bgfx::ShaderHandle vertexShader =
      bgfx::createShader(loadShader("src/shaders/vs.sc.bin"));
  bgfx::ShaderHandle fragmentShader =
      bgfx::createShader(loadShader("src/shaders/fs.sc.bin"));

  bgfx::ProgramHandle shaderProgram =
      bgfx::createProgram(vertexShader, fragmentShader, true);

  struct Vertex {
    float x, y;
    uint32_t color;
  };

  bgfx::VertexLayout vertexLayout;
  bgfx::VertexBufferHandle vbo;
  bgfx::IndexBufferHandle ibo;

  static Vertex squareVertices[] = {
      {-1.0f, 1.0f, 0xFF0000FF},  // Top-left (Red)
      {1.0f, 1.0f, 0xFF00FF00},   // Top-right (Green)
      {-1.0f, -1.0f, 0xFFFF0000}, // Bottom-left (Blue)
      {1.0f, -1.0f, 0xFFFFFF00}   // Bottom-right (Yellow)
  };
  static const uint16_t squareIndices[] = {
      0, 2, 1, // First triangle
      1, 2, 3  // Second triangle
  };

  vertexLayout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  vbo = bgfx::createVertexBuffer(
      bgfx::makeRef(squareVertices, sizeof(squareVertices)), vertexLayout);
  ibo = bgfx::createIndexBuffer(
      bgfx::makeRef(squareIndices, sizeof(squareIndices)));

  if (!bgfx::isValid(shaderProgram)) {
    printf("invalid shader");
  } else {
    printf("good shader");
  }

  while (!window.shouldClose()) {
    window.pollEvents();
    bgfx::setVertexBuffer(0, vbo);
    bgfx::setIndexBuffer(ibo);
    bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::submit(0, shaderProgram);
    renderer.renderFrame();
  }

  return 0;
}
