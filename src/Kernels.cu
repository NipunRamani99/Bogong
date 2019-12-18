#include <cuda_runtime.h>
#include <cuda.h>
#include "../Extra/helper_functions.h"    // includes cuda.h and cuda_runtime_api.h

// CUDA helper functions
#include "../Extra/helper_cuda.h"         // helper functions for CUDA error check
#include<iostream>
#include "../include/StableFluid/StableFluidKernels.h"

float t = 0.0f;
surface<void, cudaSurfaceType2D> surfRef;
__global__ void TextureUpdate(int width, int height,float time)
{
	int x = blockIdx.x*blockDim.x+threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	float4 colour = { 0.0f,1.0f,1.0f,1.0f };
	float xx =(float) x / (float)width;
	float yy = (float)y / (float)height;
	colour.x = 0.5f + 0.5f * sinf( xx + 0 + time);
	colour.y = 0.5f + 0.5f * sinf( yy + 2 + time);
	colour.z = 0.5f + 0.5f * sinf( xx + 4 + time);
	surf2Dwrite(colour, surfRef, x * sizeof(float4), y);
	
}   
void WashColor(cudaArray_t array, int width, int height, float delT)
{
	t += delT;
	checkCudaErrors(cudaBindSurfaceToArray(surfRef, array));
	dim3 block(16, 16);
	dim3 grid(width/block.x, height/block.y);
	TextureUpdate <<< grid,block >>>(width,height,t); 	
	
}
