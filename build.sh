# make build dir
mkdir build && cd build

# run cmake
cmake -DCMAKE_BUILD_TYPE=Release ..

# compile all
make

echo "Build success! Compiled to build/LZW_Decompressor"
echo "Syntax: ./LZW_Decompressor a.txt.z b.txt.z ..."
echo "Or use chmod +x test.sh && ./tesh.sh for a demo run."