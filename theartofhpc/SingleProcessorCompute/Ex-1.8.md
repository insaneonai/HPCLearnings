### Question

In the example of direct mapped caches, mapping from memory to cache was
done by using the final 16 bits of a 32 bit memory address as cache address. Show that
the problems in this example go away if the mapping is done by using the first (‘most
significant’) 16 bits as the cache address. Why is this not a good solution in general?


### Answer:
In a direct-mapped cache, each memory address is mapped to exactly one cache location. In the given example, memory addresses are 32 bits long and the cache contains 8K words. The original mapping scheme uses the least significant bits of the memory address as the cache index. As a result, two memory locations separated by 8K words have identical lower address bits and are mapped to the same cache location. When both locations are accessed repeatedly, they continuously evict each other from the cache, leading to poor performance.

One possible solution is to use the most significant bits of the address as the cache index instead of the least significant bits. In this case, addresses that differ by 8K words would usually have different cache indices because the conflict-causing lower bits are no longer used for indexing. Therefore, the specific problem described in the example would disappear.

However, this approach introduces a much more serious problem. Programs typically exhibit spatial locality, meaning that if one memory location is accessed, nearby locations are likely to be accessed soon afterward. Consecutive memory addresses usually differ only in their lower bits while their upper bits remain unchanged. If the cache index is derived from the most significant bits, many nearby addresses will map to the same cache location.

Thus, while using the most significant bits eliminates the conflict between addresses separated by 8K words, it destroys the cache's ability to exploit spatial locality. Since most programs access memory sequentially or in nearby regions, this would lead to much worse overall cache performance.