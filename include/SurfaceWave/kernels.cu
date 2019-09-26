#include <cuda_runtime.h>
#include "RunCuda.hpp"
/////////////////////////////////////////////////////////////////////////////////
////! Simple kernel to modify vertex positions in sine wave pattern
////! @param data  data in global memory
/////////////////////////////////////////////////////////////////////////////////
__global__ void simple_vbo_kernel_(float3 *pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

	// calculate uv coordinates
	float u = x / (float)width;
	float v = y / (float)height;
	u = u * 2.0f - 1.0f;
	v = v * 2.0f - 1.0f;

	// calculate simple sine wave pattern
	float freq = 4.0f;
	float w = sinf(u*freq + time) * cosf(v*freq + time) * 0.5f;

	// write output vertex
	pos[y*width + x] = make_float3(u, w, v);
}

__global__ void simple_vbo_kernel_2(float3 *pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

	float u = pos[y*width + x].x;
	float v = pos[y*width + x].y;
	float w = pos[y*width + x].z;
}

void UpdateMesh_(float3 *pos, unsigned int mesh_width,
	unsigned int mesh_height, float time)
{
	// execute the kernel
	dim3 block(8, 8, 1);
	dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
	simple_vbo_kernel_<< < grid, block >> > (pos, mesh_width, mesh_height, time);
	simple_vbo_kernel_2 << <grid, block >> > (pos, mesh_width, mesh_height,time);
}
