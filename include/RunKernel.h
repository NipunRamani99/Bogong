#pragma once
#include "../Extra/helper_functions.h"
#include "../Extra/helper_cuda.h"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
struct WaveProp
{
	float amplitude = 0.0f;
	float q = 0.0f;
	float dirx = 0;
	float diry = 0;
	int isCircular = 0x00;
	float phase = 0.0f;
	float x = 0;
	float y = 0;
	float w = 0;
};
struct MeshProp
{
	unsigned int mesh_height = 100;
	unsigned int mesh_width = 100;
};
void UpdateMesh(float3 *pos, unsigned int width, unsigned int height,float time);
void UpdateColors(float4 *pos, unsigned int width, unsigned int height,float time);
void UpdateGrid(float3 * pos, unsigned int width, unsigned int height, float time);
void GerstnerTest(float3 * pos, unsigned int mesh_width, unsigned int mesh_height, float amplitude, float time);
void GerstnerTest(float3 * pos, WaveProp * prop, MeshProp mesh,int n ,float time);
void GerstnerNormalTest(float3 * pos, float3 * norms,WaveProp * prop, MeshProp mesh, int n, float time);
