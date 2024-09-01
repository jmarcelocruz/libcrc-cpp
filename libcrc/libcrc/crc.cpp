#include <libcrc/crc.hpp>

namespace {
    uint8_t reflected_byte(uint8_t b) {
        uint8_t a{0};
        for (int i = 0; i < 8; i++) {
            a = (a << 1) | ((b >> i) & 0x01);
        }

        return a;
    }
}

namespace crc {
    Crc8::Crc8(uint8_t generator, uint8_t remainder, uint8_t final_xor, bool reflect_input, bool reflect_output)
        : generator{generator}
        , remainder{remainder}
        , final_xor{final_xor}
        , reflect_input{reflect_input}
        , reflect_output{reflect_output} {}

    uint8_t Crc8::crc(uint8_t* first, uint8_t* last) {
        uint8_t crc = remainder;
        for (; first < last; first++) {
            crc ^= reflect_input ? reflected_byte(*first) : *first;
            for (uint8_t i = 8; i > 0; --i) {
                if (crc & 0x80) {
                    crc = (crc << 1) ^ generator;
                } else {
                    crc = (crc << 1);
                }
            }
        }

        return (reflect_output ? reflected_byte(crc) : crc) ^ final_xor;
    }
}
