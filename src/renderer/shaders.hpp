#ifndef SHADERS_H
#define SHADERS_H

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
                    bgfx::DynamicVertexBufferHandle pixelsBuffer);

public:
  bgfx::VertexBufferHandle vbo;
  bgfx::IndexBufferHandle ibo;
  bgfx::ProgramHandle shaderProgram;

  bgfx::ProgramHandle posGenProgram;
  bgfx::ProgramHandle sphProgram;
  bgfx::DynamicVertexBufferHandle projectileBuffer;
  bgfx::DynamicVertexBufferHandle pixelsBuffer;
};

#endif
