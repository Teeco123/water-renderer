#include "utils.hpp"

const bgfx::Memory *loadShader(const char *filename) {
  bx::FileReader fileReader;
  if (!bx::open(&fileReader, filename)) {
    printf("Failed to open shader file: %s\n", filename);
    return nullptr;
  }

  // Get file size
  bx::Error err;
  uint32_t size = (uint32_t)bx::getSize(&fileReader);

  // Allocate memory for shader
  const bgfx::Memory *mem = bgfx::alloc(size + 1);

  // Read file content into memory
  bx::read(&fileReader, mem->data, size, &err);

  // Null-terminate for safety
  mem->data[size] = '\0';
  bx::close(&fileReader);
  return mem;
}
