#include <libcrc/crc.hpp>

namespace {
    template<typename T>
    T reflected(T b) {
        T a{0};
        for (int i = 0; i < sizeof(T) * 8; i++) {
            a = (a << 1) | ((b >> i) & 0x01);
        }

        return a;
    }
}

namespace crc {
    template<typename T>
    Crc<T>::Crc(T generator, T remainder, T final_xor, bool reflect_input, bool reflect_output)
        : generator{generator}
        , remainder{remainder}
        , final_xor{final_xor}
        , reflect_input{reflect_input}
        , reflect_output{reflect_output} {}

    template<typename T>
    T Crc<T>::crc(uint8_t* first, uint8_t* last) {
        T crc = remainder;
        for (; first < last; first++) {
            crc ^= ((reflect_input ? reflected(*first) : *first) << ((sizeof(T) - 1) * 8));
            for (uint8_t i = 8; i > 0; --i) {
                if (crc & (1u << (sizeof(T) * 8 - 1))) {
                    crc = (crc << 1) ^ generator;
                } else {
                    crc = (crc << 1);
                }
            }
        }

        return (reflect_output ? reflected(crc) : crc) ^ final_xor;
    }
}
