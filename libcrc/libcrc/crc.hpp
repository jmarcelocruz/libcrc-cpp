#ifndef LIBCRC_CRC_HPP
#define LIBCRC_CRC_HPP

#include <cstdint>

namespace crc {
    template<typename T>
    class Crc {
    public:
        Crc(T generator, T remainder = 0, T final_xor = 0, bool reflect_input = false, bool reflect_output = false);
        T crc(uint8_t* first, uint8_t* last);

    private:
        const T final_xor;
        const T generator;
        const bool reflect_input;
        const bool reflect_output;
        const T remainder;
    };

    template class Crc<uint8_t>;
    template class Crc<uint32_t>;

    using Crc8 = Crc<uint8_t>;
    using Crc32 = Crc<uint32_t>;
}

#endif
