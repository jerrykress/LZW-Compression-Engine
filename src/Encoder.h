#pragma once

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Cqueue.h"

namespace lzw
{
    class Encoder
    {
    public:
        Encoder() = delete;
        Encoder(int cw_width, int default_dict_size = 256);
        Encoder(const Encoder &that) = delete;
        Encoder &operator=(Encoder &that) = delete;

        void encode(std::string filename);

    private:
        void init_default_dict_();
        void reset_dict_();

        int cw_width_;
        int dict_entry_idx_;
        const int dict_capacity_;
        const int default_dict_size_;
        std::unordered_map<std::string, uint16_t> default_dict_;
        std::unordered_map<std::string, uint16_t> dict_;
    };
}