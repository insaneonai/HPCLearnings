### Question

How does the LRU replacement policy relate to direct-mapped versus associative caches?

### Answer

In a **direct-mapped cache**, each memory block maps to exactly one cache line. If a new block maps to an already occupied line, the existing block must be evicted. Since there is no choice regarding which line to replace, an LRU policy is unnecessary.

In an **associative cache**, a memory block can be placed in multiple possible locations. When all available lines are occupied, the cache needs a replacement policy to decide which block to evict. LRU (Least Recently Used) replaces the block that has not been accessed for the longest time.

For example, in a 4-way associative cache, we can use 2-bit counters to represent the relative ages of the cache lines:

- `0` represents the most recently used (MRU) line.
- `3` represents the least recently used (LRU) line.

On a cache hit, the accessed line becomes the MRU, and the other counters are updated to maintain the relative ordering. On a cache miss, the line with rank `3` is evicted, and the newly loaded block becomes the MRU.

These counters represent relative ranks rather than the total number of accesses, so their values remain between `0` and `3`, avoiding ordinary counter overflow.

**In short:** LRU is unnecessary for direct-mapped caches because the replacement location is predetermined, whereas associative caches can use LRU to choose which block to evict.
