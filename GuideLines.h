#pragma once
#include<glm/glm.hpp>
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Model.h"
class GuideLines :public Mesh 
{
	
public:
	GuideLines()
	{
		m_IsConstructed = false;
	}
	GuideLines(glm::vec3 p_Pos)
		:
		Mesh(p_Pos)
	{
		
		Vertex<float> posX;
		Vertex<float> negX;
		Vertex<float> posY;
		Vertex<float> negY;
		Vertex<float> posZ;
		Vertex<float> negZ;
	
		posX.x = 100.0f;
		posX.r = 1.0f;
		posX.a = 1.0f;
		posY.y = 100.0f;
		posY.r = 1.0f;
		posY.a = 1.0f;
		posZ.z = 100.0f;
		posZ.r = 1.0f;
		posZ.a = 1.0f;
		
		negX.x = -100.0f;
		negX.r = 1.0f;
		negX.a = 1.0f;
		negY.y = -100.0f;
		negY.r = 1.0f;
		negY.a = 1.0f;
		negZ.z = -100.0f;
		negZ.r = 100.0f;
		negZ.a = 1.0f;

		m_Vertices.push_back(posX);
		m_Vertices.push_back(negX);
		m_Vertices.push_back(posY);
		m_Vertices.push_back(negY);
		m_Vertices.push_back(posZ);
		m_Vertices.push_back(negZ);
		m_Indices.push_back(0);
		m_Indices.push_back(1);
		m_Indices.push_back(2);
		m_Indices.push_back(3);
		m_Indices.push_back(4);
		m_Indices.push_back(5);

		m_VAO = VertexArray();
		m_VBO = VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex<float>));
		m_IBO = IndexBuffer(m_Indices.data(), m_Indices.size() * sizeof(unsigned int));
		m_Mode = GL_LINES;
			
		    
	}
	GuideLines(GuideLines && gl)
		:
		Mesh(std::move(gl))
	{

	}
	GuideLines & operator=(GuideLines && p_GuideLines)
	{
		Mesh::operator=(std::move(p_GuideLines));
		return *this;
		
	}
	GuideLines & operator=(GuideLines & p_GuideLines)
	{		
		return *this;
	}
	
    ~GuideLines()
	{
		if (m_IsConstructed)
			std::cout << "Guide Lines with Model ID: " << id << " has been destroyed.";
	}
};