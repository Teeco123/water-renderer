#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <bgfx/bgfx.h>
#include <bx/file.h>
#include <cstdio>

// Function to load shader from a file
const bgfx::Memory *loadShader(const char *filename);

#endif // SHADER_LOADER_H
