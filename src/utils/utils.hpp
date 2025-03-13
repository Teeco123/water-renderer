#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <bgfx/bgfx.h>
#include <bx/file.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

// Function to load shader from a file
const bgfx::Memory *loadShader(const char *filename);
int GetRandomValue(int min, int max);

#endif // SHADER_LOADER_H
