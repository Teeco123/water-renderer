echo "Running CMake configuration..."
cmake -S . -B build

echo "Building the project..."
make -C build

rm -rf build/bin/src

shaderc -f src/shaders/posGen.compute -o src/shaders/posGen.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
shaderc -f src/shaders/calcDensity.compute -o src/shaders/calcDensity.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
shaderc -f src/shaders/sph.compute -o src/shaders/sph.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
shaderc -f src/shaders/shader.vertex -o src/shaders/shader.vertex.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type vertex
shaderc -f src/shaders/shader.fragment -o src/shaders/shader.fragment.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type fragment

mkdir build/bin/src
cp -r src/shaders build/bin/src/shaders/

echo "Running the project..."
./build/bin/WaterRenderer
