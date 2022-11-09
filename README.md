# LZW-Compression-Engine

Compression and decompression utility based on a fixed width variant of LZW algorithm (12 bit in the included compressor). Reads and writes files in a streaming fashion so only minimal memory is used.

## Compile

Clone the repo and run the build script. Requires: **Cmake, g++/clang++**

The final compiled binary is named `Compressor` in build folder.

```
chmod +x build.sh && ./build.sh
```

## How to use

```
# compress files
./Compressor -c file_1 file_2 ...

# extract files
./Compressor -x file_1.z file_2.z ...
```
