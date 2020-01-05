#include <cuda_runtime.h>
#include <cuda.h>
#include "../Extra/helper_functions.h"    // includes cuda.h and cuda_runtime_api.h

// CUDA helper functions
#include "../Extra/helper_cuda.h"         // helper functions for CUDA error check
#include<iostream>
#include "cuda_allocations.hpp"

void AllocateData(void ** devPtr, void * data, size_t size) {
	cudaMalloc(devPtr, size);
	if (data != nullptr) {
		checkCudaErrors(cudaMemcpy(*devPtr,data,size,cudaMemcpyHostToDevice));
	}
}
void FreeData(void * devPtr) {
	cudaFree(devPtr);
}