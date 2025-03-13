#ifndef SHADERS_H
#define SHADERS_H

#include "bx/file.h"
#include <bgfx/bgfx.h>
#include <iostream>

class Shaders {
public:
  Shaders();
  ~Shaders();

  void submitShader(bgfx::VertexBufferHandle vbo, bgfx::IndexBufferHandle ibo,
                    bgfx::ProgramHandle shaderProgram);

public:
  bgfx::VertexBufferHandle vbo;
  bgfx::IndexBufferHandle ibo;
  bgfx::ProgramHandle shaderProgram;
};

#endif
