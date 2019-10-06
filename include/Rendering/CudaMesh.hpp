#pragma once
#include "../CudaVBO.h"
#include "../VertexArray.hpp"
#include "../VertexBufferLayout.hpp"
#include "../IndexBuffer.h"
#include <vector>
#include <memory>
#include <utility>
namespace bogong {
	namespace cuda {
		typedef std::pair<std::shared_ptr<VertexBuffer>, VertexBufferLayout> Buffer;
		
		class CudaMesh
		{
		protected:
			std::vector<float3> m_VertPos;
			std::vector<float4> m_Color;
			VertexArray m_VAO;
			std::vector<Buffer> m_BufferVertex;
			IndexBuffer m_IBO;
			long int count = 0;
		public:
			CudaMesh()
			{

			}
			/*CudaMesh(CudaMesh && mesh)
			{
				m_VertPos = std::move(mesh.m_VertPos);
				m_Color = std::move(mesh.m_Color);
				m_VAO = std::move(mesh.m_VAO);
				m_BufferVertex = std::move(mesh.m_BufferVertex);
				m_IBO = std::move(mesh.m_IBO);
				m_VBO1 = std::move(mesh.m_VBO1);
				m_VBO2 = std::move(mesh.m_VBO2);
				count = mesh.count;

			}
			CudaMesh & operator=(CudaMesh&& mesh)
			{
				m_VertPos = std::move(mesh.m_VertPos);
				m_Color = std::move(mesh.m_Color);
				m_VAO = std::move(mesh.m_VAO);
				m_BufferVertex = std::move(mesh.m_BufferVertex);
				m_IBO = std::move(mesh.m_IBO);
				m_VBO1 = std::move(mesh.m_VBO1);
				m_VBO2 = std::move(mesh.m_VBO2);
				count = mesh.count;
				return *this;
			}*/
		
			std::vector<Buffer> & GetBufferVertex()
			{
				return m_BufferVertex;
			}
			void Bind()
			{
				int i = 0;
				for (auto& buffer : m_BufferVertex)
				{
					for (auto & elem : buffer.second.GetElements())
					{
						glEnableVertexAttribArray(i);
						i++;
					}
				}
				i = 0;
				for (auto & pair : m_BufferVertex)
				{
					auto buffer = pair.first.get();
					buffer->Bind();
					auto elements = pair.second.GetElements();
					int offset = 0;
					for (auto & elem : elements)
					{
						auto k = i;
						auto count = elem.count;
						auto type = elem.type;
						auto isNormalized = elem.isNormalized;
						auto stride =  pair.second.GetStride();
						glVertexAttribPointer(i, count, type, isNormalized, stride, (void*)offset);
						offset += elem.count * sizeof(float);
						i++;
					}
				}
				if (m_IBO.GetID() != 0)
					m_IBO.Bind();
			}
			void Unbind()
			{
				int i = 0;
				for (auto& buffer : m_BufferVertex)
				{
					buffer.first.get()->Unbind();
					auto elems = buffer.second.GetElements();
					for (auto & v : elems)
					{
						glDisableVertexAttribArray(i);
						i++;
					}

				}
			}
		    IndexBuffer GetIndexBuffer()
			{
				return m_IBO;
			}
			int GetCount()
			{
				return count;
			}
		};
	}
}
