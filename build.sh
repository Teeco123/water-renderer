echo "Running CMake configuration..."
cmake -S . -B build

echo "Building the project..."
make -C build

rm -rf build/bin/src

SHADERC=./lib/bgfx-cmake/build/cmake/bgfx/shaderc

$SHADERC -f src/shaders/posGen.compute -o src/shaders/posGen.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
$SHADERC -f src/shaders/step1.compute -o src/shaders/step1.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
$SHADERC -f src/shaders/step2.compute -o src/shaders/step2.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
$SHADERC -f src/shaders/step3.compute -o src/shaders/step3.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
$SHADERC -f src/shaders/step4.compute -o src/shaders/step4.compute.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type compute
$SHADERC -f src/shaders/shader.vertex -o src/shaders/shader.vertex.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type vertex
$SHADERC -f src/shaders/shader.fragment -o src/shaders/shader.fragment.bin -i lib/bgfx-cmake/bgfx/src --platform osx -p metal --type fragment

mkdir build/bin/src
cp -r src/shaders build/bin/src/shaders/

echo "Running the project..."
./build/bin/WaterRenderer
