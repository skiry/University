#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUN_KARATSUBA 1

static void HandleError(cudaError_t err,
    const char *file,
    int line) {
    if (err != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err),
            file, line);
        exit(EXIT_FAILURE);
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

cudaError_t classicalCuda(int *c, const int *a, const int *b, unsigned int size);
cudaError_t karatsubaCuda(int *c, const int *a, const int *b, unsigned int size);
cudaError_t karatsubaCudaCorrect(int *c, const int *a, const int *b, unsigned int size);

__device__ void multiplyKernelKaratsubaRec(int *z, const int *x, const int *y, const int size)
{
    const int *a, *b, *c, *d;
    int *ab, *ac;
    int *bd, *cd;
    int *adbc;


    if (size <= 1)
    {
        z[0] = x[0] * y[0];
    }
    else
    {
        int half = (int)size / 2;

        ab = (int*)malloc(half * sizeof(int));
        ac = (int*)malloc(half * sizeof(int));
        cd = (int*)malloc(half * sizeof(int));
        bd = (int*)malloc(half * sizeof(int));
        adbc = (int*)malloc(half * sizeof(int));

        a = x;
        b = x + half;

        c = y;
        d = y + half;

        multiplyKernelKaratsubaRec(ac, a, c, half);
        multiplyKernelKaratsubaRec(bd, b, d, size - half);

        int i = 0;
        for (i = 0; i < half; i++)
        {
            ab[i] = a[i] + b[i];
            cd[i] = c[i] + d[i];
        }

        multiplyKernelKaratsubaRec(adbc, ab, cd, half);

        for (i = 0; i < half; i++)
        {
            z[i] = adbc[i] - ac[i] - bd[i];
        }
    }
}

__global__ void multiplyKernelKaratsuba(int *z, const int *x, const int *y, const int size)
{
    multiplyKernelKaratsubaRec(z, x, y, size);
}

__global__ void multiplyKernel(int *c, const int *a, const int *b, const int size)
{
    int i = threadIdx.x;
    for (int j = 0; j < size; ++j) {
        c[i + j] += a[i] * b[j];
    }
}


int* generatePolynome(const int size)
{
    int *pol = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        pol[i] = rand() % 2020;
    return pol;
}

int main()
{
    const int arraySize = 64000;
    const int* a = generatePolynome(arraySize);
    const int* b = generatePolynome(arraySize);
    int c[2 * arraySize] = { 0 };

    /*
    float time;
    cudaEvent_t start, stop;

    HANDLE_ERROR(cudaEventCreate(&start));
    HANDLE_ERROR(cudaEventCreate(&stop));
    HANDLE_ERROR(cudaEventRecord(start, 0));
    */
    time_t timeStart;
    time_t timeEnd;

    time(&timeStart);

    cudaError_t cudaStatus;

    if (RUN_KARATSUBA) {
        // Multiply vectors in parallel with the karatsuba algorithm
        cudaStatus = karatsubaCudaCorrect(c, a, b, arraySize);
    }
    else {
        // Multiply vectors in parallel with the n squared algorithm
        cudaStatus = classicalCuda(c, a, b, arraySize);
    }

    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "multiplyWithCuda failed!");
        return 1;
    }

    time(&timeEnd);
    /*
    HANDLE_ERROR(cudaEventRecord(stop, 0));
    HANDLE_ERROR(cudaEventSynchronize(stop));
    HANDLE_ERROR(cudaEventElapsedTime(&time, start, stop));
    */
    printf("Time to multiply:  %3.1lld ms \n", timeEnd - timeStart);

    /*for (int i = 0; i < arraySize; i++)
        printf("%d ", a[i]);

    printf("\n\n");

    for (int i = 0; i < arraySize; i++)
        printf("%d ", b[i]);

    printf("\n\n");

    for (int i = 0; i < 2 * arraySize - 1; i++)
        printf("%d ", c[i]);

    printf("\n");*/

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}

// Helper function for using CUDA to multiply vectors in parallel.
cudaError_t classicalCuda(int *c, const int *a, const int *b, unsigned int size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, 2 * size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    multiplyKernel<<<1, size>>>(dev_c, dev_a, dev_b, size);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "multiplydKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching multiplyKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, 2 * size * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
    
    return cudaStatus;
}

cudaError_t karatsubaCudaCorrect(int *c, const int *a, const int *b, unsigned int size) {
    int *dev_a = nullptr;
    int *dev_b = nullptr;
    int *dev_c = nullptr;
    cudaError_t cudaStatus;

    cudaSetDevice(0);

    cudaMalloc(&dev_c, 2 * size * sizeof(int));
    cudaMalloc(&dev_a, size * sizeof(int));
    cudaMalloc(&dev_b, size * sizeof(int));

    cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);

    int thread_num = 2 * size;
    multiplyKernelKaratsuba << <1, thread_num >> > (dev_c, dev_a, dev_b, size);

    cudaStatus = cudaDeviceSynchronize();

    cudaMemcpy(c, dev_c, 2 * size * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);

    return cudaSuccess;
}

// Helper function for using CUDA to multiply vectors in parallel.
cudaError_t karatsubaCuda(int *c, const int *a, const int *b, unsigned int size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, 2 * size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    multiplyKernelKaratsuba << <1, 2 * size >> > (dev_c, dev_a, dev_b, size);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "multiplydKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }

    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching multiplyKernelKaratsuba!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, 2 * size * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);

    return cudaStatus;
}
