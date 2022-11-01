// This is a demo of how the library can be used in other projects to decode LZW encoded files
// Syntax: ./LZW_Decompressor <file_1> <file_2> ...

#include <chrono>
#include <iostream>
#include "LzwDecoder.h"
#define DECODER_CW_WIDTH 12

int main(int argc, char **argv)
{
    lzw::Decoder decoder(DECODER_CW_WIDTH);

    auto start = std::chrono::high_resolution_clock::now();

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            std::cout << "[+] " << argv[i] << "\n";
            decoder.decode(argv[i]);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = end - start;
    std::cout << "\nDecoded " << argc - 1 << " files in " << duration.count() << " seconds\n";

    return 0;
}