#include "LzwEncoder.h"

namespace lzw
{
    Encoder::Encoder(int cw_width, int default_dict_size) : cw_width_(cw_width), default_dict_size_(default_dict_size), dict_capacity_(std::pow(2, cw_width))
    {
        init_default_dict_();
    }

    void Encoder::encode(std::string filename)
    {
        std::ifstream file_in(filename, std::ifstream::in | std::ifstream::binary);
        std::ofstream file_out(filename + ".lz", std::ofstream::out | std::ofstream::binary);

        Cqueue bit_q(std::ceil(cw_width_ / 8.0) * 16);
        char char_buf;
        std::string read_buf;

        reset_dict_();
        file_in.read(&char_buf, 1);

        while (file_in.good() || bit_q.available())
        {
            if (!bit_q.contains(8))
            {
                read_buf = char_buf;

                if (dict_entry_idx_ == dict_capacity_)
                    reset_dict_();

                while (dict_.find(read_buf) != dict_.end())
                {
                    file_in.read(&char_buf, 1);
                    read_buf += char_buf;
                }

                dict_[read_buf] = dict_entry_idx_++;
                read_buf.pop_back();

                int cw_val = dict_[read_buf];

                for (int shift = cw_width_ - 1; shift >= 0; shift--)
                    bit_q.write(cw_val >> shift & 0x1);
            }

            else
            {
                int code = 0;

                for (int bit = 0; bit < 8; bit++)
                    code = code * 2 + bit_q.read();

                char c = '\x00' + code;

                file_out.write(&c, 1);
            }
        }
        file_in.close();
        file_out.close();

        std::cout << "Remain in queue: " << bit_q.available() << "\n";
    }

    void Encoder::init_default_dict_()
    {
        if (default_dict_.empty())
        {
            for (int i = 0; i < default_dict_size_; i++)
            {
                default_dict_.emplace(std::string(1, '\x00' + i), i);
            }
        }
    }

    void Encoder::reset_dict_()
    {
        dict_ = default_dict_;
        dict_entry_idx_ = default_dict_size_;
    }
}