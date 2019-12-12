#include <cuda_runtime.h>

#include "../include/StableFluid/StableFluidKernels.h"

__global__ void ColourizeKernel(float4 * surface,int width, int height)
{
	int x = blockIdx.x*blockDim.x + threadIdx.x;
	int y = blockIdx.y*blockDim.y + threadIdx.y;
	
	surface[x + y * width].x = 1.0f;
	surface[x + y * width].y = 0.0f;
	surface[x + y * width].z = 0.0f;
	surface[x + y * width].w = 1.0f;

}
void WashColor(float4 * surface, unsigned int width, unsigned int height,float t)
{
	dim3 block(16, 16, 1);
	dim3 grid(width / block.x, height / block.y, 1);
	ColourizeKernel << <grid, block >> > (surface, width, height);
}
