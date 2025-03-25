#ifndef COMPUTE_PROGRAM_HPP
#define COMPUTE_PROGRAM_HPP

#include "baseProgram.hpp"

class ComputeProgram : public BaseProgram {
private:
  const char *name;
  bgfx::ShaderHandle computeShader;
  bgfx::ProgramHandle program;
  uint32_t groupX, groupY, groupZ;

public:
  ComputeProgram(const char *compute, uint32_t groupXInt, uint32_t groupYInt,
                 uint32_t groupZInt);
  void submit() override;
  void destroy() override;

  bgfx::ProgramHandle Get() const;

  ~ComputeProgram();
};

#endif
