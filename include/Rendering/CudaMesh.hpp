#pragma once
#include "../CudaVBO.h"
#include "../VertexArray.hpp"
#include "../VertexBufferLayout.hpp"
#include "../IndexBuffer.h"
#include "../Texture.h"
#include <vector>
#include <memory>
#include <utility>
namespace bogong {  
	namespace cuda {
		typedef std::pair<std::shared_ptr<VertexBuffer>, VertexBufferLayout> Buffer;
		
		class CudaMesh
		{
		protected:
			std::vector<std::shared_ptr<Texture>> m_TexVector;
			std::vector<Buffer> m_BufferVertex;
			IndexBuffer m_IBO;
			size_t count = 0;
		public:
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
				assert(!error());
				for (auto & pair : m_BufferVertex)
				{
					auto buffer = pair.first.get();
					buffer->Bind();
					auto elements = pair.second.GetElements();
					int offset = 0;
					assert(!error());
					for (auto & elem : elements)
					{
						auto k = i;
						auto count = elem.count;
						auto type = elem.type;
						auto isNormalized = elem.isNormalized;
						auto stride =  pair.second.GetStride();
						glVertexAttribPointer(i, count, type, isNormalized, stride, (const void *)offset);
						offset += elem.count * sizeof(float);
						i++;
					}
				}
				assert(!error());
				if (m_IBO.GetID())
					m_IBO.Bind();
				for (auto & t : m_TexVector) {
					t->Bind();
				}
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
			size_t GetCount()
			{
				return count;
			}
		};
	}
}
