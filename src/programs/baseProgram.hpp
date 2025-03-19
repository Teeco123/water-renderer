#ifndef BASE_PROGRAM_HPP
#define BASE_PROGRAM_HPP

#include "../utils/types.hpp"
#include "../utils/utils.hpp"
#include <bgfx/bgfx.h>
#include <string.h>
#include <string>

class BaseProgram {
public:
  virtual void init() = 0;
  virtual void submit() = 0;
  virtual void destroy() = 0;
  virtual ~BaseProgram() {}
};

#endif
