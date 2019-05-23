#pragma once
#include <vector>
#include <GL/glew.h>
#include <gl/gl.h>

struct BufferElement
{
	unsigned int type = GL_FLOAT;
	unsigned int isNormalized = GL_FALSE;
	int count = 0;
	BufferElement(unsigned int p_Type, unsigned int p_IsNormalized,int p_Count)
	{
		count = p_Count;
		isNormalized = p_IsNormalized;
		type = p_Type;

	}
};
class VertexBufferLayout
{
private:
	std::vector<BufferElement> m_Elements;
	int m_Stride = 0;
public:
	VertexBufferLayout() = default;

	template<typename ElemType>
	void AddElement(int p_Count)
	{
		if (ElemType == float)
			m_Elements.push_back({ GL_FLOAT,GL_FALSE,p_Count });
		if (ElemType == unsigned int)
			m_Elements.push_back({ GL_UNSIGNED_INT,GL_FALSE,p_Count });
		m_Stride += sizeof(ElemType) * p_Count;
	}
	std::vector<BufferElement> & getElements()
	{
		return m_Elements;
	}
};