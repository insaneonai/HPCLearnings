#include <cuda_runtime.h>
#include <random>

__global__ void matrix_multiplication_kernel(const float* A, const float* B, float* C, int M, int N,
                                             int K) {
                                                int col = blockIdx.x * blockDim.x + threadIdx.x;
                                                int row = blockIdx.y * blockDim.y + threadIdx.y;

                                                if (row < M && col < K){
                                                    float sum = 0.0f;
                                                    for (int i=0; i<N; i++){
                                                        sum += A[row * N + i] * B[i*K + col];
                                                    }
                                                    C[row * K + col] = sum;
                                                }

                                             }

void validateResult(const float* C, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%8.4f ", C[row * cols + col]);
        }
        printf("\n");
    }
}

int main() {
    float *A = (float*)malloc(sizeof(float) * 1024);
    float *B = (float*)malloc(sizeof(float) * 1024);
    float *C = (float*)malloc(sizeof(float) * 1024);

    float *d_A=nullptr, *d_B=nullptr, *d_C=nullptr;

    cudaMalloc((void**)&d_A, sizeof(float) * 1024);
    cudaMalloc((void**)&d_B, sizeof(float) * 1024);
    cudaMalloc((void**)&d_C, sizeof(float) * 1024);

    // Initialize A and B in host memory randomly
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < 1024; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    cudaMemcpy(d_A, A, sizeof(float) * 1024, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeof(float) * 1024, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C, sizeof(float) * 1024, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16); // 16x16 = 256 threads per block
    dim3 numBlocks(2, 2); // 2x2 = 4 blocks to cover 32x32 matrix

    matrix_multiplication_kernel<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, 32, 32, 32);

    cudaDeviceSynchronize();
    cudaMemcpy(C, d_C, sizeof(float) * 1024, cudaMemcpyDeviceToHost);

    validateResult(C, 32, 32);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}
