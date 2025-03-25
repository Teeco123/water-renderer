#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "baseProgram.hpp"

class ShaderProgram : public BaseProgram {
private:
  bgfx::ShaderHandle vertexShader;
  bgfx::ShaderHandle fragmentShader;
  bgfx::ProgramHandle program;

public:
  ShaderProgram(const char *vertex, const char *fragment);
  void submit() override;
  void destroy() override;

  bgfx::ProgramHandle Get() const;

  ~ShaderProgram();
};

#endif
