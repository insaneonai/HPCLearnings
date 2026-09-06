# Recursive Doubling for a Recurrence with Dependencies

## Question

Consider the following recurrence:

```c
for (int i = 0; i < size; ++i) {
    x[i+1] = a[i] * x[i] + b[i];
}
```

This operation cannot be directly handled by a pipeline because there is a dependency between the input of one iteration and the output of the previous iteration.

However, the loop can be transformed into a mathematically equivalent computation using **recursive doubling**.

1. Derive an expression that computes \(x[i+2]\) directly from \(x[i]\), without involving \(x[i+1]\).
2. Analyze the efficiency of the recursive-doubling scheme by deriving formulas for \(T_0(n)\) and \(T_s(n)\).
3. Explain why, for the constant-coefficient case,

$$
x_{i+n}
=
a_i^n x_i
+
a_i^{n-1}b_i
+
a_i^{n-2}b_i
+\cdots+
a_i b_i
+
b_i.
$$

---

## 1. Original Recurrence

The original computation is

$$
x[i+1] = a[i]x[i] + b[i].
$$

The computation of \(x[i+1]\) depends on \(x[i]\), which itself depends on \(x[i-1]\). Therefore, the iterations form a dependency chain:

$$
x_0 \rightarrow x_1 \rightarrow x_2 \rightarrow x_3 \rightarrow \cdots
$$

As a result, the iterations cannot be executed independently in parallel.

Assuming one recurrence operation takes time \(t\), computing \(n\) elements sequentially takes

$$
\boxed{T_0(n)=nt}.
$$

---

## 2. Deriving the Recursive-Doubling Expression

Starting with

$$
x[i+1] = a[i]x[i] + b[i],
$$

we have

$$
x[i+2] = a[i+1]x[i+1] + b[i+1].
$$

Substituting the expression for \(x[i+1]\),

$$
x[i+2]
=
a[i+1]\left(a[i]x[i]+b[i]\right)+b[i+1].
$$

Expanding,

$$
x[i+2]
=
a[i+1]a[i]x[i]
+
a[i+1]b[i]
+
b[i+1].
$$

Therefore,

$$
\boxed{
x[i+2]
=
a[i+1]a[i]x[i]
+
a[i+1]b[i]
+
b[i+1]
}
$$

This expression computes \(x[i+2]\) directly from \(x[i]\), eliminating the dependency on \(x[i+1]\).

---

## 3. Why This Enables Parallelism

The original dependency chain is

$$
x_i \rightarrow x_{i+1} \rightarrow x_{i+2}
\rightarrow x_{i+3}\rightarrow\cdots
$$

Recursive doubling changes this to

$$
x_i \rightarrow x_{i+2} \rightarrow x_{i+4}
\rightarrow x_{i+8}\rightarrow\cdots
$$

At each doubling stage, multiple computations can be performed independently.

For example, after transforming the recurrence, computations such as

$$
x_0\rightarrow x_2,
\qquad
x_1\rightarrow x_3,
\qquad
x_2\rightarrow x_4,
\qquad
x_3\rightarrow x_5
$$

can be organized into parallel operations.

The important idea is that the number of sequential dependency levels is reduced from \(n\) to approximately

$$
\log_2 n.
$$

Thus, with sufficiently many processors, the critical-path time becomes

$$
\boxed{
T_s(n)=O(\log_2 n)t
}
$$

instead of \(O(n)t\).

More precisely, under the idealized model where each doubling stage takes time \(t\),

$$
\boxed{
T_s(n)\approx \lceil\log_2 n\rceil t
}
$$

apart from the constant-time preliminary and final calculations.

---

## 4. Computing the Missing Terms

Once the even-indexed terms are computed,

$$
x_i,\ x_{i+2},\ x_{i+4},\ x_{i+8},\ldots
$$

the missing terms can be calculated independently using the original recurrence:

$$
x_{i+2k+1}
=
a[i+2k]x[i+2k]+b[i+2k].
$$

Since each missing term now depends only on an already-computed even term, these calculations can also be performed in parallel.

Therefore, the recursive-doubling approach reduces the sequential dependency depth from

$$
O(n)
$$

to

$$
\boxed{O(\log n)}.
$$

---

## 5. Deriving the General Expression

For a constant \(a\) and \(b\), the recurrence becomes

$$
x_{i+1}=ax_i+b.
$$

Applying it once:

$$
x_{i+1}=ax_i+b.
$$

Applying it twice:

$$
x_{i+2}
=
a(ax_i+b)+b
=
a^2x_i+ab+b.
$$

Applying it three times:

$$
x_{i+3}
=
a(a^2x_i+ab+b)+b
$$

$$
=
a^3x_i+a^2b+ab+b.
$$

Continuing this pattern gives

$$
\boxed{
x_{i+n}
=
a^n x_i
+
a^{n-1}b
+
a^{n-2}b
+\cdots+
ab+b
}
$$

This can also be written as

$$
\boxed{
x_{i+n}
=
a^n x_i
+
b\sum_{k=0}^{n-1}a^k
}
$$

and, when \(a\neq1\),

$$
\boxed{
x_{i+n}
=
a^n x_i
+
b\frac{a^n-1}{a-1}
}
$$

---

## 6. Efficiency Comparison

The original sequential computation has

$$
\boxed{T_0(n)=nt}.
$$

With recursive doubling and sufficient parallel processors, the dependency depth is logarithmic:

$$
\boxed{
T_s(n)\approx\lceil\log_2 n\rceil t
}
$$

Therefore, the idealized speedup is approximately

$$
S(n)
=
\frac{T_0(n)}{T_s(n)}
$$

$$
=
\frac{nt}{\lceil\log_2 n\rceil t}
$$

and hence

$$
\boxed{
S(n)\approx
\frac{n}{\log_2 n}
}
$$

for large \(n\).

Thus, recursive doubling changes the computation from a sequential \(O(n)\) dependency chain into a parallel computation with \(O(\log n)\) critical-path depth.

---

## Final Results

$$
\boxed{T_0(n)=nt}
$$

$$
\boxed{
x[i+2]
=
a[i+1]a[i]x[i]
+
a[i+1]b[i]
+
b[i+1]
}
$$

$$
\boxed{
T_s(n)\approx\lceil\log_2 n\rceil t
}
$$

$$
\boxed{
S(n)\approx\frac{n}{\log_2 n}
}
$$

For constant \(a\) and \(b\),

$$
\boxed{
x_{i+n}
=
a^n x_i+
a^{n-1}b+
a^{n-2}b+
\cdots+
ab+b
}
$$

The key advantage of recursive doubling is that it reduces the **dependency depth** from \(O(n)\) to \(O(\log n)\), allowing the computation to exploit parallelism.
