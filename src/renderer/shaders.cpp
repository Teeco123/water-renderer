#include "shaders.hpp"
#include "bgfx/bgfx.h"
#include <cstdint>

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

  bgfx::ShaderHandle posGenShader =
      bgfx::createShader(loadShader("src/shaders/posGen.compute.bin"));
  this->posGenProgram = bgfx::createProgram(posGenShader);
  bgfx::ShaderHandle sphShader =
      bgfx::createShader(loadShader("src/shaders/sph.compute.bin"));
  this->sphProgram = bgfx::createProgram(sphShader);

  //------------------------------------------------------------------------------------
  // Layout for projectiles
  bgfx::VertexLayout projectileLayout;
  projectileLayout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .end();

  uint32_t projectileCount = 1 * 256;
  uint32_t posBufferstride = projectileLayout.getStride();
  uint32_t posBufferSize = projectileCount * posBufferSize;

  this->projectileBuffer = bgfx::createDynamicVertexBuffer(
      posBufferSize, projectileLayout, BGFX_BUFFER_COMPUTE_READ_WRITE);

  //------------------------------------------------------------------------------------
  // Layout for pixels on screen
  bgfx::VertexLayout pixelsLayout;
  pixelsLayout.begin()
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
      .end();

  this->radius = 10;
  this->resolution = {800, 800};
  this->pixelsCount = resolution.x * resolution.y;
  uint32_t pixelsBufferStride = pixelsLayout.getStride();
  uint32_t pixelsBufferSize = pixelsCount * pixelsBufferStride;

  this->pixelsBuffer = bgfx::createDynamicVertexBuffer(
      pixelsBufferSize, pixelsLayout, BGFX_BUFFER_COMPUTE_READ_WRITE);

  //------------------------------------------------------------------------------------
  // Setting uniforms
  u_numPoints = bgfx::createUniform("u_numPoints", bgfx::UniformType::Vec4);
  u_radius = bgfx::createUniform("u_radius", bgfx::UniformType::Vec4);
  u_resolution = bgfx::createUniform("u_resolution", bgfx::UniformType::Vec4);
}

Shaders::~Shaders() {
  bgfx::destroy(vbo);
  bgfx::destroy(ibo);
  bgfx::destroy(shaderProgram);
  bgfx::destroy(posGenProgram);
  bgfx::destroy(sphProgram);
  bgfx::destroy(projectileBuffer);
  bgfx::destroy(pixelsBuffer);
  bgfx::destroy(u_numPoints);
  bgfx::destroy(u_radius);
  bgfx::destroy(u_resolution);
}

void Shaders::submitShader(bgfx::VertexBufferHandle vbo,
                           bgfx::IndexBufferHandle ibo,
                           bgfx::ProgramHandle shaderProgram,
                           bgfx::ProgramHandle posGenProgram,
                           bgfx::ProgramHandle sphProgram,
                           bgfx::DynamicVertexBufferHandle projectileBuffer,
                           bgfx::DynamicVertexBufferHandle pixelsBuffer,
                           bgfx::UniformHandle u_numPoints,
                           bgfx::UniformHandle u_radius,
                           bgfx::UniformHandle u_resolution, float pixelsCount,
                           float radius, Vec2 resolution) {

  //------------------------------------------------------------------------------------
  // Submit shader to render in while loop
  bgfx::setBuffer(0, projectileBuffer, bgfx::Access::ReadWrite);
  bgfx::dispatch(0, posGenProgram, 256 / 256, 1, 1);
  bgfx::frame();

  bgfx::setBuffer(0, projectileBuffer, bgfx::Access::ReadWrite);
  bgfx::setBuffer(1, pixelsBuffer, bgfx::Access::ReadWrite);
  bgfx::dispatch(0, sphProgram, 800 / 15, 800 / 15, 1);
  bgfx::frame();

  bgfx::setVertexBuffer(0, vbo);
  bgfx::setIndexBuffer(ibo);
  bgfx::setUniform(u_numPoints, &pixelsCount);
  bgfx::setUniform(u_radius, &radius);
  bgfx::setUniform(u_resolution, &resolution);
  bgfx::setBuffer(0, projectileBuffer, bgfx::Access::Read);
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(0, shaderProgram);
}
