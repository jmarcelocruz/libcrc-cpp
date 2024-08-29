#include <libcrc/crc.hpp>

namespace crc {
    Crc8::Crc8(uint8_t generator, uint8_t remainder, uint8_t final_xor)
        : generator{generator}
        , remainder{remainder}
        , final_xor{final_xor} {}

    uint8_t Crc8::crc(uint8_t* first, uint8_t* last) {
        uint8_t crc = remainder;
        for (; first < last; first++) {
            crc ^= *first;
            for (uint8_t i = 8; i > 0; --i) {
                if (crc & 0x80) {
                    crc = (crc << 1) ^ generator;
                } else {
                    crc = (crc << 1);
                }
            }
        }

        return crc ^ final_xor;
    }
}
