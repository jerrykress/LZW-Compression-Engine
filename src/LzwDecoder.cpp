#include "LzwDecoder.h"

namespace lzw
{

    Decoder::Decoder(int cw_width) : cw_width_(cw_width), dict_capacity_(std::pow(2, cw_width))
    {
        cw_dict_.reserve(dict_capacity_);
    }

    Decoder::~Decoder()
    {
    }

    void Decoder::decode(std::string filename)
    {
        std::ifstream file_in(filename, std::ios::in | std::ios::binary);
        std::ofstream file_out({filename.begin(), filename.end() - 2}, std::ios::out | std::ios::binary);

        Cqueue q_bin(16);

        char char_in;

        reset_dict_();

        while (file_in.good())
        {
            if (!q_bin.contains(cw_width_))
            {
                file_in.read(&char_in, 1);
                for (int shift = 7; shift >= 0; shift--)
                {
                    q_bin.write(char_in >> shift & 0x1);
                }
            }
            else
            {
                int code = 0;

                for (int bit = 0; bit < cw_width_; bit++)
                {
                    code = code * 2 + q_bin.read();
                }
                // if dict full then reset
                if (dict_idx_ == dict_capacity_)
                    reset_dict_();

                // if this is not the first entry, amend the last one
                if (dict_idx_ != 256)
                    cw_dict_[dict_idx_ - 1] += cw_dict_[code][0];

                // complete own entry
                cw_dict_[dict_idx_++] = cw_dict_[code];
                file_out << cw_dict_[code];
            }
        }

        file_in.close();
        file_out.close();
    }

    void Decoder::reset_dict_()
    {
        cw_dict_.resize(256);
        std::iota(cw_dict_.begin(), cw_dict_.end(), '\x00');
        dict_idx_ = 256;
    }
}