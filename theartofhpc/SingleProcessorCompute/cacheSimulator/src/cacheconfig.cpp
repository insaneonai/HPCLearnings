
#include <cmath>
#include "cacheconfig.h"

CacheConfig::CacheConfig(size_t cache_size, size_t block_size, size_t associativity) {
    this->cache_size = cache_size;
    this->block_size = block_size;
    this->associativity = associativity;

    this->index_bits = static_cast<uint8_t>(std::log2(cache_size / (block_size * associativity)));
    this->offset_bits = static_cast<uint8_t>(std::log2(block_size));

    this->tag_bits = 64 - this->index_bits - this->offset_bits;
}