// This is a demo of how the library can be used in other projects to decode LZW encoded files
// Syntax: ./LZW_Decompressor <file_1> <file_2> ...

#include <chrono>
#include <iostream>
#include "Decoder.h"
#include "Encoder.h"

#define DECODER_CW_WIDTH 12

int main(int argc, char **argv)
{
    lzw::Decoder decoder(DECODER_CW_WIDTH);
    lzw::Encoder encoder(DECODER_CW_WIDTH);

    auto start = std::chrono::high_resolution_clock::now();

    if (argc > 2)
    {
        // if compressing files
        if (std::string opt = argv[1]; opt == "-c")
        {
            for (int i = 2; i < argc; i++)
            {
                std::string f = argv[i];
                encoder.encode(f);
                std::cout << "[-] " << f << " -> " << f + ".z\n";
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float> duration = end - start;
            std::cout << "\nEncoded " << argc - 2 << " files in " << duration.count() << " seconds\n";
        }
        // if decompressing files
        else if (opt == "-x")
        {
            for (int i = 2; i < argc; i++)
            {
                std::string f = argv[i];
                decoder.decode(f);
                std::cout << "[+] " << f << " -> " << f.substr(0, f.size() - 2) << "\n";
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float> duration = end - start;
            std::cout << "\nDecoded " << argc - 2 << " files in " << duration.count() << " seconds\n";
        }
    }
    else
    {
        std::cout << "[x] Bad arguments. Please provide option and filepaths\n";
    }

    return 0;
}