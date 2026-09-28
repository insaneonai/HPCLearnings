# MSI Cache Coherence: Writes and Memory Updates

Consider two processors with private caches containing cache lines \(x_1\) and \(x_2\), corresponding to memory location \(x\).

The MSI states are:

- **M (Modified)**: Cache has the only valid and most recent copy.
- **S (Shared)**: Multiple caches may have the line and memory is up-to-date.
- **I (Invalid)**: Cache line is not valid.

---

# Initial Reads

Initially:

$$
(x_1,x_2) = (I,I)
$$

Processor \(P_1\) reads \(x\):

$$
(I,I) \rightarrow (S,I)
$$

Processor \(P_2\) then reads \(x\):

$$
(S,I) \rightarrow (S,S)
$$

At this point:

- Both caches contain the same value.
- Memory is up-to-date.

---

# Write by \(P_1\)

Suppose \(P_1\) writes to \(x\).

Before:

$$
(S,S)
$$

To gain exclusive ownership, \(P_1\) invalidates \(P_2\)'s copy:

$$
(S,S) \rightarrow (M,I)
$$

Now:

- \(P_1\) owns the only valid copy.
- Memory may contain an old value.
- \(P_1\)'s cache contains the newest value.

---

# Important Observation

A line in state \(M\) does **not** immediately write back to memory.

The processor may continue modifying the line:

$$
(M,I)
\rightarrow
(M,I)
\rightarrow
(M,I)
\rightarrow
\cdots
$$

while memory remains stale.

This avoids unnecessary memory traffic.

---

# When Does Memory Get Updated?

## Case 1: Modified Line Is Evicted

Suppose \(P_1\) must remove the cache line.

Before eviction:

$$
(M,I)
$$

The modified value is written back:

$$
(M,I)
\rightarrow
\text{Memory Writeback}
\rightarrow
(I,I)
$$

Thus:

$$
\boxed{M \rightarrow \text{Memory}}
$$

is allowed directly.

The cache line does **not** need to become Shared first.

---

## Case 2: Another Processor Reads

Suppose \(P_2\) reads while \(P_1\) has the line in Modified state.

Before:

$$
(M,I)
$$

After:

$$
(M,I)
\rightarrow
(S,S)
$$

The updated value is supplied to \(P_2\).

Now:

- Both caches have a copy.
- Both copies are identical.
- Memory may be updated as part of the transaction depending on the implementation.

---

# Key Question

> Do we need to reach \((S,S)\) before writing to memory?

**No.**

A modified line may be written directly back to memory during eviction:

$$
(M,I)
\rightarrow
\text{Memory}
\rightarrow
(I,I)
$$

without ever passing through:

$$
(S,S)
$$

---

# Intuition

Think of MSI as:

### Shared (S)

$$
\boxed{\text{Memory and cache agree}}
$$

Memory contains the latest value.

---

### Modified (M)

$$
\boxed{\text{Cache has the newest value}}
$$

Memory may be stale.

---

### Invalid (I)

$$
\boxed{\text{Cache copy cannot be used}}
$$

---

# Typical Transition Sequence

Read by \(P_1\):

$$
(I,I)
\rightarrow
(S,I)
$$

Read by \(P_2\):

$$
(S,I)
\rightarrow
(S,S)
$$

Write by \(P_1\):

$$
(S,S)
\rightarrow
(M,I)
$$

Another read by \(P_2\):

$$
(M,I)
\rightarrow
(S,S)
$$

Write by \(P_2\):

$$
(S,S)
\rightarrow
(I,M)
$$

Eviction of modified line:

$$
(I,M)
\rightarrow
\text{Memory Writeback}
\rightarrow
(I,I)
$$

---

# Memory Bandwidth Usage

Memory bandwidth is used when:

$$
(I,I) \rightarrow (S,I)
$$

(first read miss)

$$
(S,I) \rightarrow (S,S)
$$

(second processor fetches the line)

$$
(M,I) \rightarrow (S,S)
$$

(another processor requests a modified line)

$$
(M,*) \rightarrow \text{Memory}
$$

(writeback on eviction)

Memory bandwidth is **not** used when:

$$
(S,S) \rightarrow (M,I)
$$

or

$$
(S,S) \rightarrow (I,M)
$$

because these transitions only require coherence invalidation messages.

---

## Summary

The crucial MSI insight is:

$$
\boxed{\text{Modified does not mean immediately written to memory}}
$$

Instead:

$$
\boxed{M = \text{Cache owns the newest value}}
$$

and memory is updated later, typically when:

1. The line is evicted, or
2. Another processor requests the modified data.