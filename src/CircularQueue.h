
#include <vector>

namespace lzw
{
    class Cqueue
    {
    public:
        Cqueue() = delete;
        Cqueue(int capacity);
        Cqueue(const Cqueue &that) = delete;
        Cqueue &operator=(Cqueue &that) = delete;
        ~Cqueue();

        void write(bool b);
        bool contains(int i);
        bool read();

    private:
        std::vector<bool> q_;
        int capacity_;
        int written_ = 0;
        int write_idx = 0, read_idx = 0;
    };
}