#ifndef FIFO_POLICY_H
#define FIFO_POLICY_H

#include "replacementpolicy.h"
#include "cacheline.h"
#include <vector>
#include <queue>
#include <cstddef>

class FifoPolicy : public ReplacementPolicy {
private:
    std::vector<std::queue<size_t>> fifo_order;

public:
    FifoPolicy(size_t num_sets);

    size_t choose_victim(size_t set_index, const std::vector<CacheLine>& cache_lines) override;
    void onHit(size_t set_index, size_t way) override;
    void onInsert(size_t set_index, size_t way) override;
};

#endif
