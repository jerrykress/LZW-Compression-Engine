#include "LzwDecoder.h"

namespace lzw
{

    Decoder::Decoder(int cw_width) : cw_width_(cw_width), dict_capacity_(std::pow(2, cw_width))
    {
        dict_.reserve(dict_capacity_);
    }

    Decoder::~Decoder()
    {
    }

    void Decoder::decode(std::string filename)
    {
        std::ifstream file_in(filename, std::ios::in | std::ios::binary);
        std::ofstream file_out({filename.begin(), filename.end() - 2}, std::ios::out | std::ios::binary);

        Cqueue cq(16);

        char char_in;

        reset_dict_();

        while (file_in.good())
        {
            if (!cq.contains(cw_width_))
            {
                file_in.read(&char_in, 1);
                for (int shift = 7; shift >= 0; shift--)
                {
                    cq.write(char_in >> shift & 0x1);
                }
            }
            else
            {
                int code = 0;

                for (int bit = 0; bit < cw_width_; bit++)
                    code = code * 2 + cq.read();

                // if dict full then reset
                if (dict_entry_idx_ == dict_capacity_)
                    reset_dict_();

                // if this is not the first entry, amend the last one
                if (dict_entry_idx_ != default_dict_size_)
                    dict_[dict_entry_idx_ - 1] += dict_[code][0];

                // complete own entry
                dict_[dict_entry_idx_++] = dict_[code];
                file_out << dict_[code];
            }
        }

        file_in.close();
        file_out.close();
    }

    void Decoder::reset_dict_()
    {
        dict_.resize(default_dict_size_);
        std::iota(dict_.begin(), dict_.end(), '\x00');
        dict_entry_idx_ = default_dict_size_;
    }
}