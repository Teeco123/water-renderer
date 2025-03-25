#ifndef BASE_BUFFER_HPP
#define BASE_BUFFER_HPP

#include "../utils/types.hpp"
#include <bgfx/bgfx.h>
#include <string.h>
#include <string>

class BaseBuffer {
public:
  virtual void bind() = 0;
  virtual void destroy() = 0;
  virtual ~BaseBuffer() {}
};

#endif
