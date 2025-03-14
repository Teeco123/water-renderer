#include "shaders.hpp"
#include "bgfx/bgfx.h"

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
      {0.33f, 1.0f, 0xFF00FF00},  // Top-right (Green)
      {-1.0f, -1.0f, 0xFFFF0000}, // Bottom-left (Blue)
      {0.33f, -1.0f, 0xFFFFFF00}  // Bottom-right (Yellow)
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

  bgfx::ShaderHandle computeShader =
      bgfx::createShader(loadShader("src/shaders/shader.compute.bin"));
  this->computeProgram = bgfx::createProgram(computeShader);

  const uint32_t numVertices = 1000;
  const uint32_t bufferSize = numVertices * 2 * sizeof(float);
  float *vertices = new float[numVertices * 2];

  bgfx::VertexLayout computeLayout;
  computeLayout.begin().add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);

  this->computeBuffer = bgfx::createDynamicVertexBuffer(
      bgfx::makeRef(vertices, bufferSize), computeLayout,
      BGFX_BUFFER_COMPUTE_READ_WRITE);
}

Shaders::~Shaders() {
  bgfx::destroy(vbo);
  bgfx::destroy(ibo);
  bgfx::destroy(shaderProgram);
}

void Shaders::submitShader(bgfx::VertexBufferHandle vbo,
                           bgfx::IndexBufferHandle ibo,
                           bgfx::ProgramHandle shaderProgram,
                           bgfx::ProgramHandle computeProgram,
                           bgfx::DynamicVertexBufferHandle computeBuffer) {

  //------------------------------------------------------------------------------------
  // Submit shader to render in while loop
  bgfx::setBuffer(0, computeBuffer, bgfx::Access::ReadWrite);

  bgfx::dispatch(0, computeProgram);

  bgfx::setVertexBuffer(0, computeBuffer);
  bgfx::setIndexBuffer(ibo);
  bgfx::setState(BGFX_STATE_DEFAULT);

  bgfx::submit(0, shaderProgram);
}
