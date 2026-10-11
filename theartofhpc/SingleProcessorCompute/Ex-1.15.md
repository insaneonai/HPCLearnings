## Determining Whether a Kernel is Memory-Bound or Compute-Bound

To determine whether a program kernel is bandwidth-bound or compute-bound, we can use the **Roofline Model**.

First, measure the peak compute performance of the target hardware, typically in FLOPS:

$$
P_{peak} \; (\text{FLOPS})
$$

Next, determine the peak memory bandwidth:

$$
B_{peak} \; (\text{Bytes/s})
$$

The kernel's **arithmetic intensity** is then computed as:

$$
AI = \frac{\text{Total Floating Point Operations}}{\text{Total Bytes Transferred}}
$$

Using the arithmetic intensity, we can compute the maximum performance achievable under the memory bandwidth limit:

$$
P_{memory} = B_{peak} \times AI
$$

The Roofline model states that the achievable performance is bounded by:

$$
P_{attainable} = \min(P_{peak}, B_{peak} \times AI)
$$

### Determining the Bottleneck


$$
B_{peak} \times AI < P_{peak}
$$

then memory bandwidth limits performance, and the kernel is **memory-bound**.

$$
B_{peak} \times AI > P_{peak}
$$

then computation limits performance, and the kernel is **compute-bound**.

Graphically, on a roofline plot:

- Kernels that lie on the **sloped bandwidth roof** are memory-bound.
- Kernels that lie on the **flat compute roof** are compute-bound.

### Example

Suppose a processor has:

$$
P_{peak} = 1 \text{ TFLOP/s}
$$

and

$$
B_{peak} = 100 \text{ GB/s}
$$

For a kernel with arithmetic intensity:

$$
AI = 2 \text{ FLOP/Byte}
$$

the bandwidth-limited performance is:

$$
P_{memory} = 100 \times 2 = 200 \text{ GFLOP/s}
$$

Since

$$
200 \text{ GFLOP/s} < 1 \text{ TFLOP/s}
$$

the kernel is **memory-bound**.

If instead:

$$
AI = 20 \text{ FLOP/Byte}
$$

then

$$
P_{memory} = 100 \times 20 = 2 \text{ TFLOP/s}
$$

which exceeds the peak compute capability of the processor. In this case, the kernel is **compute-bound** because the processor reaches its compute limit before exhausting memory bandwidth.