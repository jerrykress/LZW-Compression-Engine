#include "Decoder.h"

namespace lzw
{
    /**
     * @brief Construct a new Decoder:: Decoder object
     *
     * @param cw_width Width of encoding (code word)
     * @param default_dict_size Size of default initialised dictionary starting from ASCII value 0, default is 256
     */
    Decoder::Decoder(int cw_width, int default_dict_size) : cw_width_(cw_width), default_dict_size_(default_dict_size), dict_capacity_(std::pow(2, cw_width))
    {
        dict_.reserve(dict_capacity_);
    }

    /**
     * @brief Decode a file using the current decoder
     *
     * @param filename Filepath
     */
    void Decoder::decode(std::string filename)
    {
        std::ifstream file_in(filename, std::ifstream::in | std::ifstream::binary);
        std::ofstream file_out(filename.substr(0, filename.size() - 2), std::ofstream::out | std::ofstream::binary);

        // circular queue, size of multiple of 8
        Cqueue bit_q(std::ceil(cw_width_ / 8.0) * 16);
        char char_buf;

        reset_dict_();

        while (file_in.good())
        {
            // read another byte if not enough bits for a code word
            if (!bit_q.contains(cw_width_))
            {
                file_in.read(&char_buf, 1);
                for (int shift = 7; shift >= 0; shift--)
                {
                    bit_q.write(char_buf >> shift & 0x1);
                }
            }
            // else translate code word
            else
            {
                int code = 0;
                // read cw_width_ bits and calc code value
                for (int bit = 0; bit < cw_width_; bit++)
                    code = code * 2 + bit_q.read();
                // reset dict when full
                if (dict_entry_idx_ == dict_capacity_)
                    reset_dict_();
                // amend last dict entry when not following the last default entry
                if (dict_entry_idx_ != default_dict_size_)
                    dict_[dict_entry_idx_ - 1] += dict_[code][0];
                // complete current entry
                dict_[dict_entry_idx_++] = dict_[code];

                file_out << dict_[code];
            }
        }

        file_in.close();
        file_out.close();
    }

    /**
     * @brief Reset the dictionary to default state
     *
     */
    void Decoder::reset_dict_()
    {
        dict_.resize(default_dict_size_);
        std::iota(dict_.begin(), dict_.end(), '\x00');
        dict_entry_idx_ = default_dict_size_;
    }
}