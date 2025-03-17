#ifndef SHADERS_H
#define SHADERS_H

#include "../utils/types.hpp"
#include "../utils/utils.hpp"
#include "bx/file.h"
#include <bgfx/bgfx.h>
#include <iostream>

class Shaders {
public:
  Shaders(const char *vertexFile, const char *fragmentFile);
  ~Shaders();

  void submitShader(bgfx::VertexBufferHandle vbo, bgfx::IndexBufferHandle ibo,
                    bgfx::ProgramHandle shaderProgram,
                    bgfx::ProgramHandle posGenProgram,
                    bgfx::ProgramHandle sphProgram,
                    bgfx::DynamicVertexBufferHandle projectileBuffer,
                    bgfx::DynamicVertexBufferHandle pixelsBuffer,
                    bgfx::UniformHandle u_numPoints,
                    bgfx::UniformHandle u_radius,
                    bgfx::UniformHandle u_resolution, float pixelsCount,
                    float radius, Vec2 resolution);

public:
  // Shader vars
  bgfx::VertexBufferHandle vbo;
  bgfx::IndexBufferHandle ibo;
  bgfx::ProgramHandle shaderProgram;

  // Compute vars
  bgfx::ProgramHandle posGenProgram;
  bgfx::ProgramHandle sphProgram;
  bgfx::DynamicVertexBufferHandle projectileBuffer;
  bgfx::DynamicVertexBufferHandle pixelsBuffer;

  // Uniform vars
  bgfx::UniformHandle u_numPoints;
  bgfx::UniformHandle u_radius;
  bgfx::UniformHandle u_resolution;

  float projectileCount;
  float radius;
  Vec2 resolution;
};

#endif
