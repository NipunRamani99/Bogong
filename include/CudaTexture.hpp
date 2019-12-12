#pragma once
#include "Texture.h"
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include "../Extra/helper_functions.h"   
//#include "../Extra/timer.h"              
#include "../Extra/helper_cuda.h"
namespace bogong {
	namespace cuda {
		class CudaTexture : public Texture
		{

			cudaGraphicsResource  * resource;
			void * devPtr;
		public:
			template<typename T>
			CudaTexture(std::vector<T>& surface, size_t width, size_t height, GLuint format, GLuint data_type, GLuint texture_target)
				:
				Texture(surface, width, height, format, data_type, texture_target)
			{
				checkCudaErrors(cudaGraphicsGLRegisterBuffer(&resource, m_TexID, cudaGraphicsRegisterFlagsNone));
			}
			CudaTexture()
			{
				checkCudaErrors(cudaGraphicsGLRegisterBuffer(&resource, m_TexID, cudaGraphicsRegisterFlagsNone));
			}
			void Map()
			{
				checkCudaErrors(cudaGraphicsMapResources(1, (cudaGraphicsResource_t*)resource, 0));
			}
			void UnMap()
			{
				checkCudaErrors(cudaGraphicsUnmapResources(1, (cudaGraphicsResource_t*)resource, 0));
			}
			void GetMappedPointer()
			{
				checkCudaErrors(cudaGraphicsResourceGetMappedPointer(&devPtr, &size, (cudaGraphicsResource_t)resource));
			}
			void * GetDataPtr()
			{
				return devPtr;
			}
		};
	}
}