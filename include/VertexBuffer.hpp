#pragma once
#include <GL/glew.h>

namespace bogong {
	
	class VertexBuffer
	{
	protected:
		unsigned int m_ID=0;
		bool m_IsBound;
		size_t m_BufferSize = 0;
	
	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer& vertexBuffer);
		VertexBuffer(const void* p_Data, size_t p_Size, unsigned int p_Draw = GL_DYNAMIC_DRAW);
		VertexBuffer& operator=(VertexBuffer& vbuff);
		VertexBuffer& operator=(const VertexBuffer& vbuff);
		void Bind() const;
		void Unbind() const;
		unsigned int getID() const;
		virtual int GetStride();
	};
}
