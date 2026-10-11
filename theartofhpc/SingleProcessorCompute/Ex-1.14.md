## Cache Reuse in Naive Matrix Multiplication

Matrix multiplication inherently exhibits data reuse because each element of matrices $A$ and $B$ participates in multiple multiply-add operations. For an $N \times N$ matrix multiplication, each element is used in approximately $O(N)$ computations. However, the existence of mathematical reuse does not automatically imply that the implementation achieves **cache reuse**.

Consider the naive triple-loop implementation:

```c
for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
        for (k = 0; k < N; k++)
            C[i][j] += A[i][k] * B[k][j];
```

### Linearized Row-Major Indexing

For a matrix stored in **row-major order**, the element at position $(i,j)$ is stored at the linearized memory index:

$$
\text{index}(i,j) = i \cdot N + j
$$

This formula allows us to determine whether a memory access pattern is **contiguous** or **strided**.

### Access Pattern of Matrix A

Inside the innermost loop, we access:

$$
A[i][k]
$$

The corresponding linearized index is:

$$
i \cdot N + k
$$

As $k$ increments by 1:

$$
iN + 0,\quad iN + 1,\quad iN + 2,\quad \ldots
$$

Adjacent accesses differ by:

$$
(iN + (k+1)) - (iN + k) = 1
$$

Since the stride is 1, these accesses are **contiguous** in memory. Consequently, a cache line fetched for one access is likely to contain several upcoming elements, resulting in good spatial locality.

### Access Pattern of Matrix B

Inside the innermost loop, we access:

$$
B[k][j]
$$

The corresponding linearized index is:

$$
k \cdot N + j
$$

As $k$ increments by 1:

$$
0N + j,\quad 1N + j,\quad 2N + j,\quad \ldots
$$

Adjacent accesses differ by:

$$
((k+1)N + j) - (kN + j) = N
$$

Thus, the stride is:

$$
\text{stride} = N
$$

For a matrix of size $1024 \times 1024$:

$$
\text{stride} = 1024
$$

This means every access jumps over 1023 intermediate elements in memory. Such accesses are **strided** rather than contiguous, leading to poor spatial locality and frequent cache misses.

### Concrete Example

Consider:

$$
N = 4
$$

The linearized layout of matrix $B$ in memory is:

| Matrix Element | Linear Index |
|---------------|-------------|
| $B[0][0]$ | 0 |
| $B[0][1]$ | 1 |
| $B[0][2]$ | 2 |
| $B[0][3]$ | 3 |
| $B[1][0]$ | 4 |
| $B[1][1]$ | 5 |
| $B[1][2]$ | 6 |
| $B[1][3]$ | 7 |

Suppose we access column $j=2$:

$$
B[0][2],\ B[1][2],\ B[2][2],\ B[3][2]
$$

The corresponding linearized indices are:

$$
2,\ 6,\ 10,\ 14
$$

The stride is:

$$
6 - 2 = 4,\quad
10 - 6 = 4,\quad
14 - 10 = 4
$$

which equals $N$.

By contrast, accessing row $i=1$:

$$
B[1][0],\ B[1][1],\ B[1][2],\ B[1][3]
$$

corresponds to:

$$
4,\ 5,\ 6,\ 7
$$

with a stride of 1, making the accesses contiguous and cache-friendly.

### Why Mathematical Reuse Does Not Guarantee Cache Reuse

Although each element of $A$ and $B$ is reused many times mathematically, cache reuse only occurs if the data remains in cache until its next use.

For sufficiently large matrices:

- Row accesses to $A$ benefit from good spatial locality.
- Column accesses to $B$ are strided and often cause cache misses.
- Previously accessed elements may be evicted before they can be reused.

As a result, mathematical reuse does not automatically translate into cache reuse.

### Factors Affecting Cache Reuse

Whether the naive implementation achieves cache reuse depends on:

- **Loop ordering** ($ijk$, $ikj$, $jik$, etc.).
- **Matrix storage layout** (row-major or column-major).
- **Cache size**, which determines whether the working set fits in cache.
- **Cache line size**, which determines how much useful data is brought in with each memory access.
- **Stride of memory accesses**, where contiguous accesses (stride = 1) are generally cache-friendly and large strides result in poor locality.

### Improving Cache Reuse with Tiling

A common optimization is **blocking (tiling)**, where matrices are divided into smaller submatrices that fit into cache. By operating on tiles, data loaded into cache can be reused many times before eviction.

The goal is to transform memory accesses from repeatedly loading large portions of the matrices into repeatedly reusing a small working set:

$$
C_{ij} = \sum_k A_{ik} B_{kj}
$$

where $A_{ik}$, $B_{kj}$, and $C_{ij}$ represent cache-sized tiles. This significantly improves cache hit rates and reduces memory traffic.

### Conclusion

Matrix multiplication exhibits significant mathematical data reuse, but a naive triple-loop implementation does not necessarily exploit this reuse at the cache level. Using the row-major linearized index formula

$$
\text{index}(i,j)=iN+j
$$

we can see that accesses to $A[i][k]$ are contiguous (stride $=1$), while accesses to $B[k][j]$ are strided (stride $=N$). Whether reuse is realized in practice therefore depends on memory access patterns, cache characteristics, and optimizations such as loop reordering and tiling.