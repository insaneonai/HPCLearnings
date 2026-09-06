#include <cuda_runtime.h>
#include <cstdio>
#include <cmath>

__global__ void vecAdd(float* A, float* B, float* C){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < 1024)  // Ensure we don't go out of bounds
		C[idx] = A[idx] + B[idx];

}

bool validateKernel(float* C, int size, float tolerance = 1e-5f) {
	// Static expected values: A[i] + B[i]
	float expected_results[10] = {11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f, 11.0f};
	
	int errorCount = 0;
	
	printf("Validating kernel results...\n");
	
	for(int i = 0; i < 10; i++) {
		float expected = expected_results[i];
		float actual = C[i];
		float error = fabs(expected - actual);
		
		// Check if error exceeds tolerance
		if(error > tolerance) {
			printf("ERROR at index [%d]: Expected %.6f, Got %.6f (error: %.6e)\n", 
				   i, expected, actual, error);
			errorCount++;
		}
	}
	
	if(errorCount == 0) {
		printf("✓ Validation PASSED! All %d elements are correct.\n", 10);
		return true;
	} else {
		printf("✗ Validation FAILED! %d/%d elements contain errors.\n", errorCount, 10);
		return false;
	}
}


int main()
{
	// Initialize A, B and C in device memory

	float A[1024] = {0};
	float B[1024] = {0};
	float C[1024] = {0};

	float *d_A=nullptr, *d_B=nullptr, *d_C=nullptr;

	cudaMalloc((void**)&d_A, sizeof(float) * 1024);
	cudaMalloc((void**)&d_B, sizeof(float) * 1024);
	cudaMalloc((void**)&d_C, sizeof(float) * 1024);

	// Initialize A and B in host memory
	float A_init[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
	float B_init[10] = {10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
	
	for(int i = 0; i < 10; i++) {
		A[i] = A_init[i];
		B[i] = B_init[i];
	}

	cudaMemcpy(d_A, A, sizeof(float) * 1024, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, B, sizeof(float) * 1024, cudaMemcpyHostToDevice);

	int threadsPerBlock = 256;
	int blocksPerGrid = (1024 + threadsPerBlock - 1) / threadsPerBlock;

	// Create CUDA events for timing
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// Record start time
	cudaEventRecord(start);

	vecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A,d_B,d_C);

	// Record stop time
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	// Calculate elapsed time
	float milliseconds = 0.0f;
	cudaEventElapsedTime(&milliseconds, start, stop);

	printf("\n=== Kernel Timing ===\n");
	printf("Execution time: %.4f ms\n", milliseconds);
	printf("Grid: (%d, 1, 1) | Blocks: (%d, 1, 1)\n", blocksPerGrid, threadsPerBlock);
	printf("Total threads: %d\n", blocksPerGrid * threadsPerBlock);
	printf("==================\n\n");

	// Clean up events
	cudaEventDestroy(start);
	cudaEventDestroy(stop);

	cudaDeviceSynchronize();

	cudaMemcpy(C, d_C, sizeof(float) * 1024, cudaMemcpyDeviceToHost);

	// Validate kernel results
	validateKernel(C, 1024);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	return 0;
}
