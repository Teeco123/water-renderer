#include "shaderProgram.hpp"
#include "bgfx/bgfx.h"
#include <iostream>

ShaderProgram::ShaderProgram(const char *vertex, const char *fragment) {

  vertexShader = bgfx::createShader(loadShader(vertex));
  fragmentShader = bgfx::createShader(loadShader(fragment));

  program = bgfx::createProgram(vertexShader, fragmentShader, true);

  if (!bgfx::isValid(program)) {
    std::cout << "Shader program is invalid\n";
  } else {
    std::cout << "Shader program is valid\n";
  }
}

void ShaderProgram::submit() {
  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::submit(0, program);
}

void ShaderProgram::destroy() {
  bgfx::destroy(vertexShader);
  bgfx::destroy(fragmentShader);
  bgfx::destroy(program);
}

ShaderProgram::~ShaderProgram() { destroy(); }
