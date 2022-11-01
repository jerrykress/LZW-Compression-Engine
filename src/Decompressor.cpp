#include <chrono>
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
            std::cout << "Decode: " << argv[i] << std::endl;
            decoder.decode(argv[i]);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "Decoded " << argc - 1 << " files in " << duration.count() << " seconds\n";

    return 0;
}