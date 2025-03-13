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

  static Vertex triangleVertices[] = {
      {0.0f, 0.5f, 0xFF0000FF},   // Red
      {-0.5f, -0.5f, 0xFF00FF00}, // Green
      {0.5f, -0.5f, 0xFFFF0000}   // Blue
  };

  vertexLayout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  vbo = bgfx::createVertexBuffer(
      bgfx::makeRef(triangleVertices, sizeof(triangleVertices)), vertexLayout);

  if (!bgfx::isValid(shaderProgram)) {
    printf("invalid shader");
  } else {
    printf("good shader");
  }

  while (!window.shouldClose()) {
    window.pollEvents();
    bgfx::setVertexBuffer(0, vbo);
    bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::submit(0, shaderProgram);
    renderer.renderFrame();
  }

  return 0;
}
