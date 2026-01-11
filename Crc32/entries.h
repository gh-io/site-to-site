#include "crc32.h"

/* Generated table (paste from crctable.out) */
static const uint32_t crctable[256] = {
    /* paste generated values here */
};

/* Compute CRC-32 */
uint32_t crc32_compute(const uint8_t *data, size_t length)
{
    uint32_t crc = CRC32_INIT;

    for (size_t i = 0; i < length; i++) {
        uint8_t index = (uint8_t)((crc ^ data[i]) & 0xFF);
        crc = (crc >> 8) ^ crctable[index];
    }

    return crc ^ CRC32_XOR;
}
