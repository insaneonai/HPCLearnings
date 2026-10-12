#ifndef CACHE_SIMULATOR_H
#define CACHE_SIMULATOR_H

#include "cacheconfig.h"
#include "replacementpolicy.h"
#include "cacheline.h"
#include <cstdint>
#include <vector>

class DecodedAddress {
    public:
        uint64_t tag;
        uint64_t index;
        uint64_t offset;
};

class CacheSimulator {
    public:
        // cache state is an array of cache lines.
        // the size of cache, cache line size, and associativity are determined from the cache configuration.
        // Use dynamic allocation to create the cache state.
        CacheConfig* config;
        ReplacementPolicy* policy;
        std::vector<std::vector<CacheLine>> sets;


        CacheSimulator(CacheConfig* config, ReplacementPolicy* policy);


        DecodedAddress decode_address(uint64_t addr);
        bool access(DecodedAddress addr); // return true if hit, false if miss


};

#endif
