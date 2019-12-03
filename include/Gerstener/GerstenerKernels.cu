#include <cuda_runtime.h>
#include "RunKernels.h"
__global__ void color_kernel2(float4 *pos, unsigned int width, unsigned int height, float time)
{
	unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
	unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;
	float xx = x / (float)width;
	float yy = y / (float)height;
	float u = 0.5f + 0.5f*cosf(time + xx + 0);
	float v = 0.5f + 0.5f*cosf(time + yy + 2);
	float w = 0.5f + 0.5f*cosf(time + xx + 4);

	// write output vertex
	pos[y*width + x] = make_float4(u, v, w, 1.0);
}
__global__ void gerstenerKernel2(float3 * pos, unsigned int width, unsigned int height, float amplitude, float time)
{
	unsigned int x = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int y = threadIdx.y + blockDim.y * blockIdx.y;
	float u = (float)x / float(width);
	float v = (float)y / float(height);
	u = u * 2.0f - 1.0f;
	v = v * 2.0f - 1.0f;
	u += 0.01f;
	v += 0.01f;
	float dix1 = -(u) / (sqrt((u*u) + (v*v)));
	float diy1 = -(v) / sqrt((u*u) + (v*v));
	float dix2 = (u - 0.45f) / (sqrt((u - 0.45f)*(u - 0.45f) + (v - 0.45f)*(v - 0.45f)));
	float diy2 = (v - 0.45f) / sqrt((u - 0.45f)*(u - 0.45f) + (v - 0.45f)*(v - 0.45f));
	float wi = 0.7;
	float q = 1.7;
	float posx = u + q * amplitude*dix1*cos((wi*((dix1)) + time) * 180 / 3.141592) + q * amplitude*dix2*cos((wi*((dix2)) + time) * 180 / 3.141592);
	float posz = v + q * amplitude*diy1*cos((wi*((diy1)) + time) * 180 / 3.141592) + q * amplitude*diy2*cos((wi*((diy2)) + time) * 180 / 3.141592);
	float posy = amplitude * sin((wi*((dix1*u) + (diy1*v)) + time) * 180 / 3.141592) + amplitude * sin((wi*((dix2*u) + (diy2*v)) + time) * 180 / 3.141592);
	pos[x + width * y] = make_float3(posx, posy, posz);

}
__global__ void multiWaveGerstenerKernelWithNormals2(float3 * pos, float3 * norms, unsigned int width, unsigned int height, WaveProp * prop, int n, float time)
{
	unsigned int x = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int y = threadIdx.y + blockDim.y * blockIdx.y;
	float u = (float)x / float(width);
	float v = (float)y / float(height);
	u = 2.0f*u - 1.0f;
	v = 2.0f*v - 1.0f;
	u += 0.01f;
	v += 0.01f;
	float posx = u;
	float posz = v;
	float posy = 0;
	float normx = 0;
	float normy = 0;
	float normz = 0;
	for (int i = 0; i < n; i++)
	{
		float dix = 0.0f, diy = 0.0f;
		if (prop[i].isCircular == 0xFF)
		{
			float x = prop[i].x;
			float y = prop[i].y;
			x = u - x;
			y = v - y;
			dix = (x) / (sqrt(x*x + y * y));
			diy = (y) / (sqrt(y*y + y * y));
		}
		else
		{
			dix = prop[i].dirx;
			diy = prop[i].diry;
		}
		float amplitude = prop[i].amplitude;
		float q = prop[i].q;
		float wi = prop[i].w;
		float phi = prop[i].phase;
		posx += q * amplitude*dix*cos((wi*((dix)) + time * phi) * 180 / 3.141592);
		posz += q * amplitude*diy*cos((wi*((diy)) + time * phi) * 180 / 3.141592);
		posy += amplitude * sin((wi*((dix*u) + (diy*v)) + time * phi) * 180 / 3.141592);
		normx += dix * wi * amplitude * sin((wi*(dix*u + diy * v) + time * phi) * 180 / 3.141592);
		normz += diy * wi * amplitude * sin(((wi*(dix*u + diy * v)) + time * phi) * 180 / 3.141592);
		normy += q * wi * amplitude * cos((wi*(dix*u + diy * v) + time * phi) * 180 / 3.141592);
	}
	normx -= normx;
	normz -= normz;
	normy = 1 - normy;
	pos[x + width * y] = make_float3(posx, posy, posz);
	norms[x + width * y] = make_float3(normx, normy, normz);

}
__global__ void multiWaveGerstenerKernel2(float3 * pos, unsigned int width, unsigned int height, WaveProp * prop, int n, float time)
{
	unsigned int x = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int y = threadIdx.y + blockDim.y * blockIdx.y;
	float u = (float)x / float(width);
	float v = (float)y / float(height);
	u = u * 2.0f - 1.0f;
	v = v * 2.0f - 1.0f;
	u += 0.01f;
	v += 0.01f;
	float posx = u;
	float posz = v;
	float posy = 0;
	for (int i = 0; i < n; i++)
	{
		float dix = 0.0f, diy = 0.0f;
		if (prop[i].isCircular == 0xFF)
		{
			float x = prop[i].x;
			float y = prop[i].y;
			x = u - x;
			y = v - y;
			dix = (x) / (sqrt(x*x + y * y));
			diy = (y) / (sqrt(y*y + y * y));
		}
		else
		{
			dix = prop[i].dirx;
			diy = prop[i].diry;
		}
		float amplitude = prop[i].amplitude;
		float q = prop[i].q;
		float wi = prop[i].w;
		float phi = prop[i].phase;
		posx += q * amplitude*dix*cos((wi*((dix)) + time * phi) * 180 / 3.141592);
		posz += q * amplitude*diy*cos((wi*((diy)) + time * phi) * 180 / 3.141592);
		posy += amplitude * sin((wi*((dix*u) + (diy*v)) + time * phi) * 180 / 3.141592);
	}
	pos[x + width * y] = make_float3(posx, posy, posz);
}
void GerstnerTest2(float3 * pos, unsigned int mesh_width, unsigned int mesh_height, float amplitude, float time)
{
	dim3 block(8, 8, 1);
	dim3 grid(mesh_width / block.x, mesh_height / block.y, 1);
	gerstenerKernel2<< < grid, block >> > (pos, mesh_width, mesh_height, amplitude, time);
}
void GerstnerNormalTest2(float3 * pos, float3 * norms, WaveProp * prop, MeshProp mesh, int n, float time)
{
	dim3 block(8, 8, 1);
	dim3 grid(mesh.mesh_width / block.x, mesh.mesh_height / block.y, 1);
	WaveProp * dev_ptr;
	checkCudaErrors(cudaMalloc(&dev_ptr, sizeof(WaveProp)*n));
	checkCudaErrors(cudaMemcpy(dev_ptr, prop, sizeof(WaveProp)*n, cudaMemcpyHostToDevice));
	multiWaveGerstenerKernelWithNormals2<< <grid, block >> > (pos, norms, mesh.mesh_width, mesh.mesh_height, dev_ptr, n, time);
	getLastCudaError("Cuda Kernel Launch failed");
	checkCudaErrors(cudaFree(dev_ptr));
}
void GerstnerTest2(float3 * pos, WaveProp * prop, MeshProp mesh, int n, float time)
{
	dim3 block(8, 8, 1);
	dim3 grid(mesh.mesh_width / block.x, mesh.mesh_height / block.y, 1);
	WaveProp * dev_ptr;
	checkCudaErrors(cudaMalloc(&dev_ptr, sizeof(WaveProp)*n));
	checkCudaErrors(cudaMemcpy(dev_ptr, prop, sizeof(WaveProp)*n, cudaMemcpyHostToDevice));
	multiWaveGerstenerKernel2<< < grid, block >> > (pos, mesh.mesh_width, mesh.mesh_height, dev_ptr, n, time);
	getLastCudaError("Cuda Kernel Launch failed");
	checkCudaErrors(cudaFree(dev_ptr));
}
void UpdateColors2(float4 * pos, unsigned int width, unsigned int height, float time)
{
	// execute the kernel
	dim3 block(8, 8, 1);
	dim3 grid(width / block.x, height / block.y, 1);
	color_kernel2<< < grid, block >> > (pos, width, height, time);
}

