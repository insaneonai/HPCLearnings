# Spatial and Temporal Locality of Tree-Based Reduction vs Sequential Summation

## Question

Consider the following algorithm for summing \(n\) numbers \(x[i]\), where \(n\) is a power of 2:

```text
for s = 2, 4, 8, ..., n:
    for i = 0 to n-1 with steps s:
        x[i] = x[i] + x[i+s/2]

sum = x[0]
```

Analyze its spatial and temporal locality, and compare it with the standard sequential summation algorithm:

```text
sum = 0
for i = 0 to n-1:
    sum += x[i]
```

# Spatial and Temporal Locality of Tree-Based Reduction vs Sequential Summation

## Tree-Based Reduction

For $n=8$:

### Stage $s=2$

```text
x[0] += x[1]
x[2] += x[3]
x[4] += x[5]
x[6] += x[7]
```

### Stage $s=4$

```text
x[0] += x[2]
x[4] += x[6]
```

### Stage $s=8$

```text
x[0] += x[4]
```

After the final stage,

$$
x[0] = \sum_{i=0}^{n-1} x[i].
$$

The total number of additions is

$$
\frac{n}{2} + \frac{n}{4} + \frac{n}{8} + \cdots + 1 = n-1.
$$

---

## Spatial Locality

At stage $s$,

$$
x[i] \leftarrow x[i] + x[i+s/2].
$$

The operand distance (stride) is

$$
\text{stride} = \frac{s}{2}.
$$

Since

$$
s = 2,4,8,\ldots,n,
$$

the stride grows as

$$
1,2,4,8,\ldots,\frac{n}{2}.
$$

Spatial locality therefore generally decreases as the reduction progresses because the operands being combined become farther apart in memory.

However, accesses remain regular and predictable within each stage.

The work performed at each level is

$$
\frac{n}{2},
\frac{n}{4},
\frac{n}{8},
\dots,
1,
$$

so most accesses occur during the early stages where locality is still good.

---

## Temporal Locality

Consider $x[0]$:

```text
s = 2 : x[0] += x[1]
s = 4 : x[0] += x[2]
s = 8 : x[0] += x[4]
...
s = n : x[0] += x[n/2]
```

The value stored in $x[0]$ is repeatedly updated throughout the reduction and therefore exhibits strong temporal locality.

However, temporal locality is unevenly distributed.

For example:

```text
x[6] += x[7]
```

After this operation, $x[7]$ is never referenced again.

Therefore:

- Leaf nodes exhibit little temporal locality.
- Surviving partial sums exhibit moderate temporal locality.
- The root node $x[0]$ exhibits the strongest temporal locality.

---

## Sequential Summation

```text
sum = 0
for i = 0 to n-1:
    sum += x[i]
```

### Spatial Locality

The array is accessed sequentially:

$$
x[0],x[1],x[2],\ldots,x[n-1].
$$

This is essentially the ideal access pattern for cache systems.

### Temporal Locality

Each array element is used exactly once:

$$
x[0],x[1],x[2],\ldots,x[n-1].
$$

Thus, the input array exhibits little temporal locality.

The accumulator

$$
\texttt{sum}
$$

is reused on every iteration:

```text
sum += x[0]
sum += x[1]
sum += x[2]
...
```

In practice, the accumulator is typically kept in a register, making its reuse extremely efficient.

---

## Single-Core vs Parallel Execution

Both algorithms perform

$$
n-1
$$

additions.

However, the reduction requires

$$
\log_2(n)
$$

stages:

```text
s = 2
s = 4
s = 8
...
s = n
```

On a single CPU core, sequential summation is typically more cache-friendly because it performs one contiguous pass over memory.

The primary advantage of tree reduction is that the operations within each stage are independent and can execute concurrently.

---

## Conclusion

The sequential algorithm provides near-optimal spatial locality through a single contiguous scan of the array. The array elements themselves exhibit little temporal locality, while the accumulator is heavily reused.

The tree-based reduction performs the same total number of additions,

$$
n-1,
$$

over

$$
\log_2(n)
$$

reduction stages. As the stride increases,

$$
1,2,4,\ldots,\frac{n}{2},
$$

spatial locality generally worsens. Temporal locality exists primarily for partial sums that survive multiple levels of the reduction tree.

Therefore:

- The sequential algorithm is generally more cache-friendly on a single CPU core.
- The tree-based reduction is preferred on multicore processors and GPUs because it exposes substantial parallelism.
``