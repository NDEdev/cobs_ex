#ifndef COBS_EX_H
#define COBS_EX_H

#include <stdint.h>
#include <stddef.h>


class cobs_ex
{
    cobs_ex();
    ~cobs_ex();

public:
    static size_t cobs_encode(const uint8_t* input, size_t length, uint8_t* output);
    static size_t cobs_decode(const uint8_t* input, size_t length, uint8_t* output);

};

#endif // COBS_EX_H
