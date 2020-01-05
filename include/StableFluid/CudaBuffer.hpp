#pragma once
#include "cuda_allocations.hpp"
namespace bogong {
	namespace cuda {
		template<typename T>
		class CudaBuffer {
		public:
			T * devPtr;
			template<typename T>
			void AllocateBuffer(std::vector<T> & vec) {
				assert(vec.data() != nullptr);
				AllocateData(&devPtr, vec.data(), vec.size() * sizeof(T));
			}
			template<typename T>
			void AllocateBuffer(T * data, size_t size)
			{
				assert(data != nullptr);
				assert(size / sizeof(data) == sizeof(T));
				AllocateData(&devPtr,data,size);
			}
			void Allocate(size_t size) {
				AllocateData(&devPtr, nullptr, size);
			}
			~CudaBuffer() {
				FreeData(devPtr);
			}
		};
	}
}