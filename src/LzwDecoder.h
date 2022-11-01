#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <numeric>
#include <stdio.h>
#include "CircularQueue.h"

namespace lzw
{
    class Decoder
    {
    public:
        Decoder() = delete;
        Decoder(int cw_width);
        Decoder(const Decoder &that) = delete;
        Decoder &operator=(Decoder &that) = delete;
        ~Decoder();

        void decode(std::string filename);

    private:
        void reset_dict_();

        int cw_width_;
        int dict_entry_idx_;
        const int dict_capacity_;
        const int default_dict_size_ = 256;
        std::vector<std::string> dict_;
    };

}