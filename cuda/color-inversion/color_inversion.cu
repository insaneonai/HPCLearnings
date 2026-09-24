#include <cuda_runtime.h>

__global__ void invert_kernel(unsigned char* image, int width, int height) {
    int pixel = blockIdx.x * blockDim.x + threadIdx.x;
    int total_pixels = width * height;

    for (int p = pixel; p < total_pixels; p += blockDim.x * gridDim.x) {
        int i = p * 4;

        image[i]     = 255 - image[i];     // R
        image[i + 1] = 255 - image[i + 1]; // G
        image[i + 2] = 255 - image[i + 2]; // B
    }
}