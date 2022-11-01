#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <numeric>
#include "CircularQueue.h"

namespace lzw
{
    /**
     * @brief LZW Decoder
     *
     */
    class Decoder
    {
    public:
        Decoder() = delete;
        Decoder(int cw_width, int default_dict_size = 256);
        Decoder(const Decoder &that) = delete;
        Decoder &operator=(Decoder &that) = delete;
        ~Decoder(){};

        void decode(std::string filename);

    private:
        void reset_dict_();

        int cw_width_;
        int dict_entry_idx_;
        const int dict_capacity_;
        const int default_dict_size_;
        std::vector<std::string> dict_;
    };

}