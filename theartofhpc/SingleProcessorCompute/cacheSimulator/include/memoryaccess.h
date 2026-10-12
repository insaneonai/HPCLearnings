#include <cstdint>
#include <iostream>

class MemoryAccess {
    public:
        uint64_t address;
        bool is_write;

        MemoryAccess(uint64_t address, bool is_write) {
            this->address = address;
            this->is_write = is_write;
        }
};
