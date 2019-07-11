#pragma once
#include "../CudaVBO.h"
#include "../VertexArray.hpp"
#include "../VertexBufferLayout.hpp"
#include "../IndexBuffer.h"
#include <vector>
namespace bogong {
	namespace cuda {
		typedef std::pair<std::shared_ptr<VertexBuffer>, VertexBufferLayout> Buffer;
		struct float3
		{
			float x;
			float y;
			float z;
		};
		struct float4
		{
			float x;
			float y;
			float z;
			float w;
		};
		class CudaMesh
		{
		protected:
			std::vector<float3> m_VertPos;
			std::vector<float4> m_Color;
			VertexArray m_VAO;
			std::vector<Buffer> m_BufferVertex;
			IndexBuffer m_IBO;
		public:
			CudaMesh()
			{

			}
			void Update()
			{
			}
			std::vector<Buffer> & GetBufferVertex()
			{
				return m_BufferVertex;
			}
		    IndexBuffer GetIndexBuffer()
			{
				return m_IBO;
			}

			int GetCount()
			{
				return m_VertPos.size();
			}
		};
	}
}
