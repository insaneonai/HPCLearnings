---

# Vector Addition - CUDA Implementation

### `/cuda/vecAddition/vecAdd.cu `

## Overview

GPU-accelerated vector addition: C[i] = A[i] + B[i]

## Implementation

- Host arrays: A[1024], B[1024], initialized with static values
- Device arrays: d_A, d_B, d_C (GPU memory)
- Grid: 4 blocks, Threads: 256 per block
- Validation: Compare against expected static results

## Observations

- The above depicts the implemnetation details of the vecAdd kernel if we look closely the Device array **d_A, d_B and d_C** resides in the GPUs Global Memory. Each 256\*4 = 1024 threads executes **C[global_idx] = A[global_idx] + B[global_idx]**.
- The instruction stream itself consumes 3 global memory operations per floating point operation.
- The arithmetic intesity thus is 1/(3\*4) = 0.083 Flops/Byte
- This makes the opreation extremely memory bound.

## Questions

1. Can moving data to shared memory work??

```
It wont work for this kernel because there is no reuse of data for this kernel.

Shared memory wont magically increase arithmetic intesity it just makes data access faster i.e cost associated with memory operations.
```

## Performance

```=== Kernel Timing ===
Execution time: 0.0072 ms
Grid: (4, 1, 1) | Blocks: (256, 1, 1)
Total threads: 1024

Validating kernel results...
✓ Validation PASSED! All 10 elements are correct.

=== Kernel Timing ===
Execution time: 0.0072 ms
Grid: (4, 1, 1) | Blocks: (256, 1, 1)
Total threads: 1024

Validating kernel results...
✓ Validation PASSED! All 10 elements are correct.

=== Kernel Timing ===
Execution time: 0.0082 ms
Grid: (4, 1, 1) | Blocks: (256, 1, 1)
Total threads: 1024

Validating kernel results...
✓ Validation PASSED! All 10 elements are correct.
```

## Roofline Analysis

Arithmetic intensity:

AI = 1 FLOP / 12 bytes
= 0.0833 FLOP/Byte

The theoretical performance ceiling is:

P <= min(P_FP32_peak, Memory_Bandwidth × AI)

Since the arithmetic intensity is very low, the memory-bandwidth
ceiling will be much lower than the GPU's FP32 compute peak.
Therefore, vector addition is memory-bandwidth bound.
