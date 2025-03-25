#include "computeProgram.hpp"
#include "bgfx/bgfx.h"
#include <iostream>

ComputeProgram::ComputeProgram(const char *compute, uint32_t groupXInt,
                               uint32_t groupYInt, uint32_t groupZInt) {

  computeShader = bgfx::createShader(loadShader(compute));
  groupX = groupXInt;
  groupY = groupYInt;
  groupZ = groupZInt;
  name = compute;

  program = bgfx::createProgram(computeShader, true);

  if (!bgfx::isValid(program)) {
    std::cout << name << " - Shader is invalid";
  } else {
    std::cout << name << " - Shader is valid";
  }
}

void ComputeProgram::submit() {
  bgfx::dispatch(0, program, groupX, groupY, groupZ);
  bgfx::frame();
}

void ComputeProgram::destroy() {
  bgfx::destroy(computeShader);
  bgfx::destroy(program);
}

ComputeProgram::~ComputeProgram() { destroy(); }
