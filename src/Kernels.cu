#include <cuda_runtime.h>

#include "../include/StableFluid/StableFluidKernels.h"

//__global__ void ColourizeKernel(float4 * colours,int width, int height,float t)
//{
//	int x = blockIdx.x*blockDim.x + threadIdx.x;
//	int y = blockIdx.y*blockDim.y + threadIdx.y;
//	float u = ;
//	colours[x + y * width].x = ;
//	colours[x + y * width].y = 0.0f;
//	colours[x + y * width].z = 0.0f;
//	colours[x + y * width].w = 1.0f;
//
//}
void WashColor(float4 * colour, unsigned int width, unsigned int height,float t)
{
	dim3 block(16, 16, 1);
	dim3 grid(width / block.x, height / block.y, 1);
	//ColourizeKernel << <grid, block >> > (pos, width, height, t);
}
