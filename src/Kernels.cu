#include <cuda_runtime.h>
#include <cuda.h>
#include "../Extra/helper_functions.h"    // includes cuda.h and cuda_runtime_api.h

// CUDA helper functions
#include "../Extra/helper_cuda.h"         // helper functions for CUDA error check
#include<iostream>
#include "../include/StableFluid/StableFluidKernels.h"

surface<void,cudaSurfaceType2D> surfRef;
__global__ void TexRead(int width, int height)
{
	int x = threadIdx.x + blockIdx.x*blockDim.x;
	int y = threadIdx.y + blockIdx.y*blockDim.y;
	float4 colour = { 0,1.0f,0,1.0f };
	surf2Dwrite(colour, surfRef, x * 4, y);
}
void WashColor(const cudaArray * array,int width,int height)
{

	checkCudaErrors(cudaBindSurfaceToArray(surfRef,array));
	dim3 block(16,16);
	dim3 grid(width/16,height/16);
	TexRead <<< grid, block >>>(width,height); 
	
}
