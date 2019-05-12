#pragma once
#include "VertexBuffer.hpp"
// includes, cuda
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
//
#include "Extra/helper_functions.h"   
#include "Extra/timer.h"              
#include "Extra/helper_cuda.h"

/////////////////////////////////////////////////////////////////////
//CudaVBO deals with Mapping/Unmapping OpenGL VBO.
//Steps to modify vertex buffer using a Cuda Kernel is:
//1.Create an Empty Buffer(Buffer Data with nullptr, specify size)
//2.Register VBO with CUDA, hold it in cudaGraphicsResource
//3.Map it before using it in kernels.
//4.Unmap it after using it in kernels.
//5.Use shaders to render the 
////////////////////////////////////////////////////////////////////
template<typename T>
class CudaVBO : public VertexBuffer
{
private:
	struct cudaGraphicsResource *cuda_vbo_resource;
	T * dataptr;
	size_t num_bytes;

public:
	T * GetData()
	{
		return dataptr;
	}
	CudaVBO() = default;
	CudaVBO( unsigned int p_Size, unsigned int p_Draw = GL_DYNAMIC_DRAW)
		:
		VertexBuffer(nullptr,p_Size,p_Draw)
	{
		RegisterVBO(m_ID, &cuda_vbo_resource, cudaGraphicsMapFlagsWriteDiscard);
	}
	void RegisterVBO(GLuint id, cudaGraphicsResource **vbo_res, unsigned int flag)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// register this buffer object with CUDA
		checkCudaErrors(cudaGraphicsGLRegisterBuffer(vbo_res, id, flag));
	}
	void Map()
	{
		checkCudaErrors(cudaGraphicsMapResources(1, &cuda_vbo_resource, 0));

	}
	void GetMappedPointer()
	{
		checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void**)&dataptr,&num_bytes,cuda_vbo_resource));
	}
	void UnMap()
	{
		checkCudaErrors(cudaGraphicsUnmapResources(1, &cuda_vbo_resource, 0));
	}

	
	
};