#include "../include/VertexBuffer.hpp"
#include <GL/glew.h>
#include <gl/gl.h>
#include "../include/Vertex.h"
bogong::VertexBuffer::VertexBuffer() = default;

bogong::VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
{
	m_ID = vertexBuffer.m_ID;
	m_IsBound = vertexBuffer.m_IsBound;
	m_BufferSize = vertexBuffer.m_BufferSize;
}

bogong::VertexBuffer::VertexBuffer(const void* p_Data, size_t p_Size, unsigned p_Draw)
{
	m_BufferSize = p_Size;
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, p_Size, p_Data, p_Draw);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bogong::VertexBuffer& bogong::VertexBuffer::operator=(VertexBuffer& vbuff)
{
	this->m_BufferSize = vbuff.m_BufferSize;
	this->m_ID = vbuff.m_ID;
	this->m_IsBound = vbuff.m_IsBound;
	return *this;
}

bogong::VertexBuffer& bogong::VertexBuffer::operator=(const VertexBuffer& vbuff)
{
	this->m_BufferSize = vbuff.m_BufferSize;
	this->m_ID = vbuff.m_ID;
	this->m_IsBound = vbuff.m_IsBound;
	return *this;
}

void bogong::VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void bogong::VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned bogong::VertexBuffer::getID() const
{
	return m_ID;
}

int bogong::VertexBuffer::GetStride()
{
	return sizeof(Vertex<float>);
}
