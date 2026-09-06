## Question

1.1. Let us compare the speed of a classical FPU, and a pipelined one. Show that the
result rate is now dependent on 𝑛: give a formula for 𝑟(𝑛), and for 𝑟∞ = lim𝑛→∞ 𝑟(𝑛).
What is the asymptotic improvement in 𝑟 over the non-pipelined case?
Next you can wonder how long it takes to get close to the asymptotic behavior. Show
that for 𝑛 = 𝑛1/2 you get 𝑟(𝑛) = 𝑟∞/2. This is often used as the definition of 𝑛1/2.

# Comparison of Classical and Pipelined FPU Result Rates

Consider an FPU with \(l\) stages, where each stage takes \(t\) units of time.

## 1. Classical (Non-Pipelined) FPU

In a classical non-pipelined FPU, one operation must pass through all \(l\) stages before the next operation can begin.

Therefore, the time required for one operation is:

$$
T_{\text{one}}=lt
$$

For \(n\) operations, the total execution time is:

$$
T_{\text{serial}}(n)=nlt
$$

The **result rate** is defined as the number of results produced per unit time:

$$
r=\frac{\text{Number of results}}{\text{Total execution time}}
$$

Thus, for the classical FPU:

$$
r_{\text{serial}}
=
\frac{n}{nlt}
$$

Therefore:

$$
\boxed{r_{\text{serial}}=\frac{1}{lt}}
$$

Hence, the non-pipelined FPU produces one result every \(lt\) units of time.

---

## 2. Pipelined FPU

In a pipelined FPU, multiple operations can be processed simultaneously in different stages.

The first operation requires \(lt\) time to pass through all \(l\) stages. After the pipeline is filled, each subsequent result is produced every \(t\) units of time.

Therefore, for \(n\) operations:

$$
T_{\text{pipeline}}(n)
=
lt+(n-1)t
$$

Simplifying:

$$
\boxed{
T_{\text{pipeline}}(n)=(l+n-1)t
}
$$

Since \(n\) results are produced in this time, the result rate is:

$$
r(n)
=
\frac{n}{T_{\text{pipeline}}(n)}
$$

Therefore:

$$
\boxed{
r(n)=\frac{n}{(l+n-1)t}
}
$$

This shows that the result rate of a pipelined FPU depends on the number of operations \(n\).

---

## 3. Asymptotic Result Rate

The asymptotic result rate is obtained when the number of operations becomes very large:

$$
r_\infty
=
\lim_{n\rightarrow\infty}r(n)
$$

Substituting \(r(n)\):

$$
r_\infty
=
\lim_{n\rightarrow\infty}
\frac{n}{(l+n-1)t}
$$

Dividing the numerator and denominator by \(n\):

$$
r_\infty
=
\frac{1}{t}
\lim_{n\rightarrow\infty}
\frac{1}
{\frac{l}{n}+1-\frac{1}{n}}
$$

As \(n\rightarrow\infty\):

$$
\frac{l}{n}\rightarrow0
$$

and

$$
\frac{1}{n}\rightarrow0
$$

Therefore:

$$
\boxed{
r_\infty=\frac{1}{t}
}
$$

Thus, after the pipeline is completely filled, one result is produced every \(t\) units of time.

---

## 4. Asymptotic Improvement over the Non-Pipelined Case

For the non-pipelined FPU:

$$
r_{\text{serial}}=\frac{1}{lt}
$$

For the pipelined FPU:

$$
r_\infty=\frac{1}{t}
$$

Therefore, the asymptotic improvement in result rate is:

$$
\frac{r_\infty}{r_{\text{serial}}}
=
\frac{\frac{1}{t}}{\frac{1}{lt}}
$$

Thus:

$$
\boxed{
\frac{r_\infty}{r_{\text{serial}}}=l
}
$$

Hence, the pipelined FPU provides an asymptotic improvement of:

$$
\boxed{l\text{ times}}
$$

compared to the non-pipelined FPU.

---

# 5. The Half-Asymptotic Point \(n\_{1/2}\)

The value \(n\_{1/2}\) represents the number of operations required for the result rate to reach half of its asymptotic value.

Therefore, by definition:

$$
r(n_{1/2})
=
\frac{r_\infty}{2}
$$

We know that:

$$
r(n)=\frac{n}{(l+n-1)t}
$$

and:

$$
r_\infty=\frac{1}{t}
$$

Thus:

$$
\frac{n_{1/2}}
{(l+n_{1/2}-1)t}
=
\frac{1}{2t}
$$

Canceling \(t\):

$$
\frac{n_{1/2}}
{l+n_{1/2}-1}
=
\frac{1}{2}
$$

Cross-multiplying:

$$
2n_{1/2}
=
l+n_{1/2}-1
$$

Therefore:

$$
n_{1/2}
=
l-1
$$

Hence:

$$
\boxed{
n_{1/2}=l-1
}
$$

---

# Final Results

The result rate of a non-pipelined FPU is:

$$
\boxed{
r_{\text{serial}}=\frac{1}{lt}
}
$$

The execution time of a pipelined FPU for \(n\) operations is:

$$
\boxed{
T_{\text{pipeline}}(n)=(l+n-1)t
}
$$

The result rate of the pipelined FPU is:

$$
\boxed{
r(n)=\frac{n}{(l+n-1)t}
}
$$

The asymptotic result rate is:

$$
\boxed{
r_\infty=\frac{1}{t}
}
$$

The asymptotic improvement over the non-pipelined FPU is:

$$
\boxed{l}
$$

The half-asymptotic point is:

$$
\boxed{
n_{1/2}=l-1
}
$$

Therefore, \(n\_{1/2}\) is the number of operations required for the pipeline to achieve half of its maximum possible result rate.
