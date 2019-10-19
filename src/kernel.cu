#include <cuda_runtime.h>
#include "../include/RunKernel.h"

__global__ void simple_vbo_kernel(float3 *pos, unsigned int width, unsigned int height, float time)
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
__global__ void color_kernel(float4 *pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;
	float xx = x / (float)width;
	float yy = y / (float)height;
	float u = 0.5f + 0.5f*cosf(time + xx + 0);
	float v = 0.5f + 0.5f*cosf(time + yy + 2);
	float w = 0.5f + 0.5f*cosf(time + xx + 4);
	
	// write output vertex
	pos[y*width + x] = make_float4(u, v, w,1.0);
}
__global__ void grid_kernel(float3 * pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;
	float u = pos[x + y * width].x;
	float v = pos[x + y * width].z;
	float freq = 4.0f;
	pos[x + y * width].x = u;   
	pos[x + y * width].z = v;
	pos[x + y * width].y = 0.5*(u*u-(v-time)*(v-time));

}
__global__ void gerstenerKernel(float3 * pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int y = threadIdx.y + blockDim.y * blockIdx.y;
	float u = (float)x /float(width);
	float v = (float)y / float(height);
	u = u * 2.0f - 1.0f;
	v = v * 2.0f - 1.0f;

	float dix = 0.707106;
	float diy = 0.707106;
	float wi = 0.7;
	float posx = u; //+ 0.5*dix*u*cos(wi*((dix*x)+(diy*v))+time);
	float posz = v;//+ 0.5*dix*v*cos(wi*((dix*u) + (diy*v)) + time);
	float posy = sin(wi*((dix*u) + (diy*v)) + time);
	pos[x + width * y] = make_float3(posx,posy,posz);

 }
void UpdateMesh(float3 *pos, unsigned int mesh_width,
	unsigned int mesh_height, float time)
{
	// execute the kernel
	dim3 block(8, 8, 1);
	dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
	simple_vbo_kernel << < grid, block >> > (pos, mesh_width, mesh_height, time);
}
void GerstnerTest(float3 * pos, unsigned int mesh_width, unsigned int mesh_height, float time)
{
	dim3 block(8, 8, 1);
	dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
	gerstenerKernel << < grid, block >> > (pos, mesh_width, mesh_height, time);
}
void UpdateColors(float4 * pos, unsigned int width, unsigned int height, float time)
{
	// execute the kernel
	dim3 block(8, 8, 1);
	dim3 grid(width / block.x, height / block.y, 1);
	color_kernel << < grid, block >> > (pos, width, height, time);
}

void UpdateGrid(float3 * pos, unsigned int width, unsigned int height, float time)
{
	dim3 block(16, 16, 1);
	dim3 grid(width / block.x, height / block.y, 1);
	grid_kernel << <grid, block >> > (pos, width, height, time);
}
