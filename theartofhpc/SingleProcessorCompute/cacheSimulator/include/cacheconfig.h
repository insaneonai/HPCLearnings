#ifndef CACHE_CONFIG_H
#define CACHE_CONFIG_H

#include <cstdint>
#include <cstddef>

class CacheConfig {
public:
    size_t cache_size; // size of cache
    size_t block_size; // size of a cache line
    size_t associativity;

    uint8_t tag_bits;
    uint8_t index_bits;
    uint8_t offset_bits;

    CacheConfig(size_t cache_size, size_t block_size, size_t associativity);
};

#endif
