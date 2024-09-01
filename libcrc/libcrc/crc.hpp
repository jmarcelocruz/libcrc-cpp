#ifndef LIBCRC_CRC_HPP
#define LIBCRC_CRC_HPP

#include <cstdint>

namespace crc {
    class Crc8 {
    public:
        Crc8(uint8_t generator, uint8_t remainder = 0, uint8_t final_xor = 0, bool reflect_input = false);
        uint8_t crc(uint8_t* first, uint8_t* last);

    private:
        const uint8_t final_xor;
        const uint8_t generator;
        const bool reflect_input;
        const uint8_t remainder;
    };
}

#endif
