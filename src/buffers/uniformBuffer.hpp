#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include "baseBuffer.hpp"

class UniformBuffer : public BaseBuffer {
private:
  bgfx::UniformHandle buffer;
  bgfx::UniformType::Enum type;
  std::string uniformName;
  Vec4 data;

public:
  UniformBuffer(const char *buffName);
  void init() override;
  void bind() override;
  void destroy() override;

  bgfx::UniformHandle Get() const;

  ~UniformBuffer();
};

#endif
