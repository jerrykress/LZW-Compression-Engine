#include "CircularQueue.h"

namespace lzw
{
    Cqueue::Cqueue(int capacity) : capacity_(capacity)
    {
        q_.reserve(capacity);
    }

    Cqueue::~Cqueue() {}

    void Cqueue::write(bool b)
    {
        if (written_ < capacity_)
        {
            q_[write_idx] = b;
            write_idx = (write_idx + 1) % capacity_;
            written_++;
        }
    }

    bool Cqueue::contains(int i)
    {
        return written_ >= i;
    }

    bool Cqueue::read()
    {
        if (written_ > 0)
        {
            bool ret = q_[read_idx];
            read_idx = (read_idx + 1) % capacity_;
            written_--;
            return ret;
        }
        return false;
    }
}