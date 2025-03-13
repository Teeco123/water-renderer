#include "Shaders.hpp"

#include "bx/file.h"
#include <iostream>

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

Shaders::Shaders(const char *vertexFile, const char *fragmentFile) {
  //------------------------------------------------------------------------------------
  // Create shader program
  bgfx::ShaderHandle vertexShader = bgfx::createShader(loadShader(vertexFile));
  bgfx::ShaderHandle fragmentShader =
      bgfx::createShader(loadShader(fragmentFile));

  this->shaderProgram = bgfx::createProgram(vertexShader, fragmentShader, true);

  if (!bgfx::isValid(shaderProgram)) {
    std::cout << "Shader is invalid";
  } else {
    std::cout << "Shader is valid";
  }

  //------------------------------------------------------------------------------------
  // create vertex verticies and index buffers
  struct Vertex {
    float x, y;
    uint32_t color;
  };

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

  bgfx::VertexLayout vertexLayout;
  vertexLayout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  this->vbo = bgfx::createVertexBuffer(
      bgfx::makeRef(squareVertices, sizeof(squareVertices)), vertexLayout);
  this->ibo = bgfx::createIndexBuffer(
      bgfx::makeRef(squareIndices, sizeof(squareIndices)));
}

Shaders::~Shaders() {}

void Shaders::submitShader(bgfx::VertexBufferHandle vbo,
                           bgfx::IndexBufferHandle ibo,
                           bgfx::ProgramHandle shaderProgram) {

  //------------------------------------------------------------------------------------
  // Submit shader to render in while loop
  bgfx::setVertexBuffer(0, vbo);
  bgfx::setIndexBuffer(ibo);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(0, shaderProgram);
}
