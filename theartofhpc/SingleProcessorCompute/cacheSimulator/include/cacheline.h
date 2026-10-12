
#ifndef CACHE_LINE_H
#define CACHE_LINE_H

#include <cstdint>

class CacheLine {
    public:
        bool valid = false;
        uint64_t tag = 0;
        // data is not needed for this simulation
        // if needed use uint8_t data[config->block_size]; and access it using offset
};

#endif // CACHE_LINE_H
