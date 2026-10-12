#ifndef REPLACEMENT_POLICY_H
#define REPLACEMENT_POLICY_H

#include <vector>
#include <cstdint>
#include "cacheline.h"

class ReplacementPolicy {
    public:
        virtual size_t choose_victim(size_t set_index, const std::vector<CacheLine>& cache_lines) = 0; // abstract method

        virtual void onHit(size_t set_index, size_t way) = 0; // abstract method
        virtual void onInsert(size_t set_index, size_t way) = 0; // abstract method
};

#endif // REPLACEMENT_POLICY_H
