#pragma once
#include "VertexBuffer.hpp"
// includes, cuda
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include "Extra/helper_functions.h"   
#include "Extra/timer.h"              
#include "Extra/helper_cuda.h"        

class CudaVBO : public VertexBuffer
{
	struct cudaGraphicsResource *cuda_vbo_resource;
	CudaVBO() = default;
	CudaVBO(const void * p_Data, unsigned int p_Size, unsigned int p_Draw = GL_DYNAMIC_DRAW)
	{
		VertexBuffer(p_Data, p_Size, p_Draw);

	}
};