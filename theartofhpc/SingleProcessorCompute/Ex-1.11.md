### Question
The recursive doubling algorithm for summing the elements of an array is:
```cpp
for (int s=2; s<2*n; s*=2)
    for (int i=0; i<n-s/2; i+=s)
        x[i] += x[i+s/2]
```
Analyze bank conflicts for this algorithm. Assume 𝑛 = 2𝑝 and banks have 2𝑘 elements
where 𝑘 < 𝑝. Also consider this as a parallel algorithm where all iterations of the inner
loop are independent, and therefore can be performed simultaneously.
Alternatively, we can use recursive halving:
```cpp
for (int s=(n+1)/2; s>1; s/=2)
    for (int i=0; i<n; i+=1)
        x[i] += x[i+s]
```
Again analyze bank conficts. Is this algorithm better? In the parallel case?

### Answer

Consider the recursive doubling reduction:

```cpp
for (int s=2; s<2*n; s*=2)
    for (int i=0; i<n-s/2; i+=s)
        x[i] += x[i+s/2];
```

Assume:

$$
n = 2^p
$$

and each memory bank contains

$$
2^k
$$

consecutive elements, where

$$
k < p.
$$

The total number of banks is therefore

$$
B=\frac{2^p}{2^k}=2^{p-k}.
$$

---

# Sequential Execution

In the sequential case, iterations of the inner loop execute one after another.

For example, during the first reduction stage:

```cpp
x[0]+=x[1]
x[2]+=x[3]
x[4]+=x[5]
x[6]+=x[7]
```

each memory access completes before the next iteration starts.

Therefore:

- Only one iteration accesses memory at a time.
- No two iterations compete for the same bank simultaneously.
- Bank conflicts do not occur.

Thus:

$$
\boxed{\text{Conflict Degree} = 1}
$$

for every stage.

Banking has no impact on performance in the purely sequential execution model.

---

# Parallel Execution

Now assume all iterations of the inner loop execute simultaneously.

At reduction stage

$$
s = 2^m
$$

the active indices are

$$
i = 0,\; 2^m,\; 2\cdot2^m,\; 3\cdot2^m,\ldots
$$

The spacing between active indices is therefore:

$$
2^m.
$$

Since each bank contains

$$
2^k
$$

elements, the number of active indices that fit inside a single bank is

$$
\frac{2^k}{2^m}
=
2^{k-m}.
$$

Hence the conflict degree at stage \(m\) is

$$
\boxed{\text{Conflict Degree}(m)=2^{k-m}}
$$

for

$$
m \le k.
$$

Once

$$
m \ge k
$$

(or equivalently \(s \ge 2^k\)), accesses are spread across different banks and conflicts disappear:

$$
\boxed{\text{Conflict Degree}=1}.
$$

---

# Example: \(p=3\) (\(n=8\))

## Case 1: \(k=0\) (1 Element/Bank)

Bank mapping:

```text
0→B0
1→B1
2→B2
3→B3
4→B4
5→B5
6→B6
7→B7
```

First reduction stage:

```cpp
x[0]+=x[1]
x[2]+=x[3]
x[4]+=x[5]
x[6]+=x[7]
```

Active indices:

```text
0, 2, 4, 6
```

Bank accesses:

```text
B0, B2, B4, B6
```

Each iteration accesses a distinct bank.

Therefore:

$$
\boxed{\text{Conflict Degree}=1}
$$

No bank conflicts.

---

## Case 2: \(k=1\) (2 Elements/Bank)

Bank mapping:

```text
0,1 → B0
2,3 → B1
4,5 → B2
6,7 → B3
```

Active indices:

```text
0, 2, 4, 6
```

Bank accesses:

```text
0 → B0
2 → B1
4 → B2
6 → B3
```

Again every active iteration accesses a different bank.

Therefore:

$$
\boxed{\text{Conflict Degree}=1}
$$

No bank conflicts.

---

## Case 3: \(k=2\) (4 Elements/Bank)

Bank mapping:

```text
0,1,2,3 → B0
4,5,6,7 → B1
```

Active indices:

```text
0, 2, 4, 6
```

Bank accesses:

```text
0 → B0
2 → B0
4 → B1
6 → B1
```

Because all iterations execute simultaneously:

```text
B0 receives 2 requests
B1 receives 2 requests
```

Therefore:

$$
\boxed{\text{Conflict Degree}=2}
$$

This is a 2-way bank conflict.

---

# Conflict Evolution Across Stages

At stage

$$
s=2^m
$$

the conflict degree is

$$
2^{k-m}.
$$

Therefore:

| Stage | Stride | Conflict Degree |
|---------|---------|---------|
| \(s=2\) | \(2^1\) | \(2^{k-1}\) |
| \(s=4\) | \(2^2\) | \(2^{k-2}\) |
| \(s=8\) | \(2^3\) | \(2^{k-3}\) |
| ... | ... | ... |
| \(s=2^k\) | \(2^k\) | 1 |

The conflict degree is halved at every stage.

---

# Worst-Case Conflict

The largest conflict occurs in the first reduction step:

$$
s=2
$$

giving

$$
\boxed{\text{Max Conflict}=2^{k-1}}
$$

Examples:

| \(k\) | Elements/Bank | Max Conflict |
|---------|---------|---------|
| 0 | 1 | 1 |
| 1 | 2 | 1 |
| 2 | 4 | 2 |
| 3 | 8 | 4 |
| 4 | 16 | 8 |
| 5 | 32 | 16 |

---

# Key Observation

### Sequential Execution

Only one iteration is active at a time:

$$
\boxed{\text{No Bank Conflicts}}
$$

Bank organization does not affect performance.

### Parallel Execution

All iterations access memory simultaneously:

- Multiple iterations may target the same bank.
- Conflict degree depends on bank size.
- Larger banks imply fewer total banks, increasing contention.

For recursive doubling:

$$
\boxed{\text{Conflict Degree}=2^{k-m}}
$$

and decreases geometrically as the stride doubles.

Therefore recursive doubling becomes increasingly bank-friendly as the reduction progresses.

The worst conflict occurs at the first stage:

$$
\boxed{\text{Max Conflict}=2^{k-1}}.
$$