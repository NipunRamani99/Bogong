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

			struct cudaGraphicsResource *resource;
			cudaArray * cuArray;
			void * devPtr;
		public:
			template<typename T>
			CudaTexture(std::vector<T>& surface, size_t width, size_t height, GLuint format, GLuint data_type, GLuint texture_target)
				:
				Texture(surface, width, height, format, data_type, texture_target)
			{
				checkCudaErrors(cudaGraphicsGLRegisterImage(&resource, m_TexID, texture_target, cudaGraphicsRegisterFlagsNone));
			}
			CudaTexture()
			{
				checkCudaErrors(cudaGraphicsGLRegisterImage(&resource, m_TexID, target,cudaGraphicsRegisterFlagsNone));
			}
			void Map()
			{
				checkCudaErrors(cudaGraphicsMapResources(1, &resource, 0));
			}
			void UnMap()
			{
				checkCudaErrors(cudaGraphicsUnmapResources(1, &resource, 0));
			}
			void GetMappedPointer()
			{
				checkCudaErrors(cudaGraphicsSubResourceGetMappedArray(&cuArray, resource, 0, 0));
			}
			void * GetDataPtr()
			{
				return devPtr;
			}
		};
	}
}