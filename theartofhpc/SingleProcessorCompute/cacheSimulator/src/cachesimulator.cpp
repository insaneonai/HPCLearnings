#include "cachesimulator.h"
#include "replacementpolicy.h"
#include <stdexcept>
#include <cstdlib>

CacheSimulator::CacheSimulator(CacheConfig* config, ReplacementPolicy* policy){
    this->config = config;
    this->policy = policy;

    // check if cache size is divisible by cache line size * associativity
    if(config->cache_size % (config->block_size * config->associativity) != 0){
        throw std::invalid_argument("Cache size must be divisible by cache line size * associativity");
    }

    int num_sets = config->cache_size / (config->block_size * config->associativity);

    this->sets.resize(num_sets);
    for(int i = 0; i < num_sets; i++){
        this->sets[i].resize(config->associativity);
    }
}

DecodedAddress CacheSimulator::decode_address(uint64_t addr){
    DecodedAddress decoded;
    decoded.tag = addr >> (this->config->index_bits + this->config->offset_bits);
    decoded.index = (addr >> this->config->offset_bits) & ((1 << this->config->index_bits) - 1);
    decoded.offset = addr & ((1 << this->config->offset_bits) - 1);
    return decoded;
}

bool CacheSimulator::access(DecodedAddress addr){
    // locate cacheline at addr.index * (config->block_size * config->associativity) + (w * config->block_size)
    int set_index = addr.index;
    
    for (size_t w=0; w<this->config->associativity; w++){
        if(this->sets[set_index][w].valid && this->sets[set_index][w].tag == addr.tag){
            policy->onHit(set_index, w);
            return true;
        }
    }

    // if miss assume data is loaded from memory
    // fill the cache line
    // find invalid way to use

    size_t way_to_use = 0;
    bool found_invalid = false;
    for (size_t w=0; w<this->config->associativity; w++){
        if (!this->sets[set_index][w].valid){
            way_to_use = w;
            found_invalid = true;
            break;
        }
    }

    if (!found_invalid){
        way_to_use = policy->choose_victim(set_index, this->sets[set_index]);
    }

    this->sets[set_index][way_to_use].valid = true;
    this->sets[set_index][way_to_use].tag = addr.tag;
    policy->onInsert(set_index, way_to_use);
    
    // miss
    return false;
    
}