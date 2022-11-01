#include "CircularQueue.h"

namespace lzw
{
    /**
     * @brief Construct a new Cqueue:: Cqueue object
     *
     * @param capacity Total capacity of circular queue
     */
    Cqueue::Cqueue(int capacity) : capacity_(capacity)
    {
        q_.reserve(capacity);
    }

    /**
     * @brief Write a bit into circular queue
     *
     * @param b
     */
    void Cqueue::write(bool b)
    {
        if (written_ < capacity_)
        {
            q_[write_idx] = b;
            write_idx = (write_idx + 1) % capacity_;
            written_++;
        }
    }

    /**
     * @brief Check whether the queue contains a number of valid bits
     *
     * @param i Number of bits
     * @return true
     * @return false
     */
    bool Cqueue::contains(int i)
    {
        return written_ >= i;
    }

    /**
     * @brief Consume a bit from the queue.
     *
     * @return true
     * @return false
     */
    bool Cqueue::read()
    {
        bool bit = false;
        if (written_ > 0)
        {
            bit = q_[read_idx];
            read_idx = (read_idx + 1) % capacity_;
            written_--;
        }
        return bit;
    }
}