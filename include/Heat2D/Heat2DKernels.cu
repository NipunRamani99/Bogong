#include <cuda_runtime.h>
#include <cuda.h>
#include "../../Extra/helper_functions.h"    // includes cuda.h and cuda_runtime_api.h

// CUDA helper functions
#include "../../Extra/helper_cuda.h"         // helper functions for CUDA error check
#include<iostream>
#include "Heat2DKernels.hpp"
surface<void, cudaSurfaceType2D> surf;
texture<float, 2>  texConstSrc;
texture<float, 2>  texIn;
texture<float, 2>  texOut;
volatile bool dstOut = true;

__device__ unsigned char value(float n1, float n2, int hue) {
	if (hue > 360)      hue -= 360;
	else if (hue < 0)   hue += 360;

	if (hue < 60)
		return (unsigned char)(255 * (n1 + (n2 - n1)*hue / 60));
	if (hue < 180)
		return (unsigned char)(255 * n2);
	if (hue < 240)
		return (unsigned char)(255 * (n1 + (n2 - n1)*(240 - hue) / 60));
	return (unsigned char)(255 * n1);
}
__global__ void float_to_color(float4 * optr,
	const float *outSrc) {
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	float l = outSrc[offset];
	float s = 1;
	int h = (180 + (int)(360.0f * outSrc[offset])) % 360;
	float m1, m2;

	if (l <= 0.5f)
		m2 = l * (1 + s);
	else
		m2 = l + s - l * s;
	m1 = 2 * l - m2;

	optr[offset].x = float(value(m1, m2, h + 120)) / 255.0f;
	optr[offset].y = float(value(m1, m2, h)) / 255.0f;
	optr[offset].z = float(value(m1, m2, h - 120)) / 255.0f;
	optr[offset].w = 1.0f;
}
__global__ void blend_kernel(float *dst,
	bool dstOut, float delta) {
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	float   t, l, c, r, b;
	if (dstOut) {
		t = tex2D(texIn, x, y - 1);
		l = tex2D(texIn, x - 1, y);
		c = tex2D(texIn, x, y);
		r = tex2D(texIn, x + 1, y);
		b = tex2D(texIn, x, y + 1);
	}
	else {
		t = tex2D(texOut, x, y - 1);
		l = tex2D(texOut, x - 1, y);
		c = tex2D(texOut, x, y);
		r = tex2D(texOut, x + 1, y);
		b = tex2D(texOut, x, y + 1);
	}
	dst[offset] = c + SPEED * (t + b + r + l - 4 * c);
}
__global__ void copy_const_kernel(float *iptr) {
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;
	float c = tex2D(texConstSrc, x, y);
	if (c != 0) {
		iptr[offset] = c;
	}
}
__global__ void WriteToTexture(float4 * frame_data) {
	const int x = threadIdx.x + blockIdx.x * blockDim.x;
	const int y = threadIdx.y + blockIdx.y * blockDim.y;
	const int offset = x + y * blockDim.x * gridDim.x;
	surf2Dwrite(frame_data[offset], surf, x * sizeof(float4), y);

}

struct DataBlock {
	float4 * output_frame;
	float * dev_inSrc;
	float * dev_outSrc;
	float * dev_constSrc;

	float totalTime;
	float frames;
};
DataBlock data_block;

void anim_gpu(DataBlock * data_block, float delta) {
	dim3 blocks(DIM / 16, DIM / 16);
	dim3 threads(16, 16);
	for (int i = 0; i < 2; i++) {
		float *in, *out;
		if (dstOut) {
			in = data_block->dev_inSrc;
			out = data_block->dev_outSrc;
		}
		else {
			out = data_block->dev_inSrc;
			in = data_block->dev_outSrc;
		}

		copy_const_kernel << <blocks, threads >> > (in);
		blend_kernel << <blocks, threads >> > (out, dstOut, delta);
		dstOut = !dstOut;
	}
	float_to_color << <blocks, threads >> > (data_block->output_frame, data_block->dev_inSrc);

}
void init_datablock() {
	size_t size = DIM * DIM * sizeof(float);
	size_t texSize = DIM * DIM * sizeof(float4);
	checkCudaErrors(cudaMalloc((void**)&data_block.output_frame, texSize));
	checkCudaErrors(cudaMalloc((void**)&data_block.dev_inSrc, size));
	checkCudaErrors(cudaMalloc((void**)&data_block.dev_outSrc, size));
	checkCudaErrors(cudaMalloc((void**)&data_block.dev_constSrc, size));
	cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
	checkCudaErrors(cudaBindTexture2D(NULL, texConstSrc, data_block.dev_constSrc, desc, DIM, DIM, sizeof(float)*DIM));
	checkCudaErrors(cudaBindTexture2D(NULL, texIn, data_block.dev_inSrc, desc, DIM, DIM, sizeof(float)*DIM));
	checkCudaErrors(cudaBindTexture2D(NULL, texOut, data_block.dev_outSrc, desc, DIM, DIM, sizeof(float)*DIM));

	//FILL IT UP WITH SHIT
	float * temp = new float[DIM*DIM];

	for (int i = 0; i < DIM*DIM; i++) {
		temp[i] = 0;
		int x = i % DIM;
		int y = i / DIM;
		if ((x > 100) && (x < 150) && (y > 250) && (y < 300))
			temp[i] = MAX_TEMP;
		else if ((x > 200) && (x < 250) && (y > 250) && (y < 300))
			temp[i] = MAX_TEMP + 1;
		else {
			temp[i] = 0.0;
		}
	}

	cudaMemcpy(data_block.dev_constSrc, temp,
		size,
		cudaMemcpyHostToDevice);
}