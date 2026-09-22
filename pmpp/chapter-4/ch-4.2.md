### Question

The following kernel is executed on a large matrix, which is tiled into
submatrices. To manipulate tiles, a new CUDA programmer has
written the following device kernel to transpose each tile in the
matrix. The tiles are of size BLOCK_SIZE by BLOCK_SIZE, and each of
the dimensions of matrix A is known to be a multiple of BLOCK_SIZE.
The kernel invocation and code are shown below. BLOCK_SIZE is
known at compile time but could be set anywhere from 1 to 20.

```
dim3 blockDim(BLOCK_SIZE,BLOCK_SIZE);
dim3 gridDim(A_width/blockDim.x,A_height/blockDim.y);
BlockTranspose<<<gridDim, blockDim>>>(A, A_width, A_height);
__global__ void
BlockTranspose(float* A_elements, int A_width, int A_height)
{
__shared__ float blockA[BLOCK_SIZE][BLOCK_SIZE];
int baseIdx ¼ blockIdx.x * BLOCK_SIZE þ threadIdx.x;
baseIdx þ¼ (blockIdx.y * BLOCK_SIZE þ threadIdx.y) * A_width;
blockA[threadIdx.y][threadIdx.x] ¼ A_elements[baseIdx];
A_elements[baseIdx] ¼ blockA[threadIdx.x][threadIdx.y];
}
```

### Answer:
If we take a look at the kernel carefully we see:
```
blockA[threadIdx.y][threadIdx.x] ¼ A_elements[baseIdx];
A_elements[baseIdx] ¼ blockA[threadIdx.x][threadIdx.y];
```

if we consider a thread (1,3) then it is responsible for writing the value A_elements[baseIdx]; but it is the thread (3,1) that is responsible for writing data to blockA[threadIdx.x][threadIdx.y].

This creates a race condition between two off-diagonal threads in the block, thus only for BLOCK_SIZE = 1 the kernel functions correctly, for BLOCK_SIZE > 1 the kernel is prone to race-condition.