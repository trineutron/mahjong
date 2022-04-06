#include <limits>

class xrand {
    uint64_t x;

   public:
    using result_type = uint32_t;
    static constexpr result_type min() {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
        return std::numeric_limits<result_type>::max();
    }
    xrand(uint64_t k) : x(k) {}
    xrand() : xrand(1) {}
    result_type operator()() {
        x ^= x << 9;
        x ^= x >> 7;
        return (x * 0x123456789abcdef) >> 32;
    }
};
