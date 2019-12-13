#include "NBodyKernels.h"
__device__ float3 bodybodyInteractions(float4 bi, float4 bj, float3 ai) {
	
	//3 FLOPS
	float3 r;
	r.x = bj.x - bi.x;
	r.y = bj.y - bi.y;
	r.z = bj.z - bi.z;
	//6 FLOPS
	float dist = r.x*r.x + r.y*r.y + r.z*r.z + EPS2;
	//3 FLOPS
	float distCube = dist * dist* dist;
	
	//2 FLOP
	float distInv = 1 / sqrtf(distCube);

	//1 FLOP
	float s = bj.w * distInv;

	ai.x += r.x * s;
	ai.y += r.y * s;
	ai.z += r.z * s;

	return ai;
}