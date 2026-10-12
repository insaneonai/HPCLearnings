#include <iostream>
#include "cacheconfig.h"
#include "memoryaccess.h"
#include "cachesimulator.h"
#include "replacementpolicy.h"
#include "fifopolicy.h"
#include <vector>

int main() {
    CacheConfig* config = new CacheConfig(1024, 64, 4);

    size_t num_sets = config->cache_size / (config->block_size * config->associativity);
    ReplacementPolicy* policy = new FifoPolicy(num_sets);

    std::vector<MemoryAccess> accesses;


    CacheSimulator simulator(config, policy);

    std::vector<uint64_t> addresses = {0x12345678, 0x12345640, 0xDEAD0078};

    // simulate cache hit miss behavior
    DecodedAddress decoded;
    for(uint64_t addr : addresses){
        decoded = simulator.decode_address(addr);

        std::cout << "Tag: 0x" << std::hex << decoded.tag << std::endl;
        std::cout << "Index: 0x" << std::hex << decoded.index << std::endl;
        std::cout << "Offset: 0x" << std::hex << decoded.offset << std::endl;

        bool hit = simulator.access(decoded);
        std::cout << "Address: 0x" << std::hex << addr << " - " << (hit ? "HIT" : "MISS") << std::endl;
    }



    return 0;
}