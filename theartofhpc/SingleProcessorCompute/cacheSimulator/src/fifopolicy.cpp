#include "fifopolicy.h"

FifoPolicy::FifoPolicy(size_t num_sets) : fifo_order(num_sets) {}

size_t FifoPolicy::choose_victim(size_t set_index, const std::vector<CacheLine>& cache_lines) {
    size_t way = fifo_order[set_index].front();
    fifo_order[set_index].pop();
    return way;
}

void FifoPolicy::onHit(size_t set_index, size_t way) {
    // FIFO doesn't need to do anything on hit
}

void FifoPolicy::onInsert(size_t set_index, size_t way) {
    fifo_order[set_index].push(way);
}
