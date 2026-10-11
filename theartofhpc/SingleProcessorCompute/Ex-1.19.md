### Question
True or false. The code
```cpp
for (int i=0; i<N; ++i)
    a[i] = b[i]+1;
```
touches every element of a and b once, so there will be a cache miss for each element

### Answer

Even though every element is touched once, accessing i, then i+1, then i+2 means neighboring elements are likely already in the same cache line. Therefore there is not a cache miss for every element. Only the first access to each cache line typically misses; subsequent accesses to elements in that line hit in cache.