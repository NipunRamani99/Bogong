#include <cuda_runtime.h>
#include <cuda.h>
#include "../Extra/helper_functions.h"    // includes cuda.h and cuda_runtime_api.h

// CUDA helper functions
#include "../Extra/helper_cuda.h"         // helper functions for CUDA error check
#include<iostream>
#include "../include/StableFluid/StableFluidKernels.h"

texture<float4, 2, cudaReadModeElementType> texRef;
__global__ void TexRead(int width, int height,float4 * devPtr)
{
	int x = threadIdx.x + blockIdx.x*blockDim.x;
	int y = threadIdx.y + blockIdx.y*blockDim.y;
	float4 colour = tex2D(texRef,x,y);
	devPtr[x + y * width] = colour;
}
void WashColor(const cudaArray * array,int width,int height)
{

	checkCudaErrors(cudaBindTextureToArray(texRef,array));
	texRef.normalized = false;
	texRef.filterMode = cudaFilterModeLinear;
	float4 * devVal;
	float4 * hostVal = new float4[width*height];
	checkCudaErrors(cudaMalloc(&devVal, width*height * sizeof(float4)));	
	dim3 block(16,16);
	dim3 grid(width/16,height/16);
	TexRead <<< grid, block >>>(width,height,devVal); 
	cudaMemcpy(hostVal, devVal, width*height * sizeof(float4), cudaMemcpyDeviceToHost);

	std::cout << hostVal[100].x << ", "<<hostVal[100].y<<", "<<hostVal[100].z<<", "<<hostVal[100].w<<"|";
	cudaUnbindTexture(texRef);
	cudaFree(devVal);
	delete hostVal;
}
