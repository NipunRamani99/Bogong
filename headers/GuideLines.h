#pragma once
#include<glm/glm.hpp>
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Mesh.h"
class GuideLines :public Mesh 
{
	VertexArray vao;
	VertexBuffer vbo;
	Shader shader;

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
		vbo = VertexBuffer(m_Vertices.data(), m_Vertices.size()*sizeof(Vertex<float>));
		    
	}
	GuideLines & operator=(GuideLines && p_GuideLines)
	{

		m_Model = std::move( p_GuideLines.m_Model );
		m_Position = std::move( p_GuideLines.m_Position );
		vao = std::move( p_GuideLines.vao );
		vbo =std::move( p_GuideLines.vbo );
		m_Vertices = std::move(p_GuideLines.m_Vertices);
		m_Indices = std::move(p_GuideLines.m_Indices);
		p_GuideLines.m_IsConstructed = false;
		m_IsConstructed = true;
	    shader = std::move(p_GuideLines.shader);
		id = p_GuideLines.id;
		return *this;
		
	}
	GuideLines & operator=(GuideLines & p_GuideLines)
	{		
		m_Indices = std::move(p_GuideLines.m_Indices);
		m_Vertices = std::move(p_GuideLines.m_Vertices);
		m_Position = std::move(p_GuideLines.m_Position);
		m_Model = std::move(p_GuideLines.m_Model);
		vao = std::move(p_GuideLines.vao);
		vbo = std::move(p_GuideLines.vbo);
		shader = std::move(p_GuideLines.shader);
		p_GuideLines.m_IsConstructed = false;
		m_IsConstructed = true;
		id = p_GuideLines.id;
		return *this;
	}
	void SetShader(Shader p_Shader)
	{
		shader = p_Shader;
		shader.setBool("isTextured", false);
	}
	void Bind()
	{
		shader.Bind();
		vao.Bind();
		vbo.Bind();
		glEnableVertexArrayAttrib(vao.GetID(), 0);
		glEnableVertexArrayAttrib(vao.GetID(), 1);
	}
	void Unbind()
	{
		glDisableVertexArrayAttrib(vao.GetID(), 0);
		glDisableVertexArrayAttrib(vao.GetID(), 1);
		vbo.Unbind();
		vao.Unbind();
		
	}
	void Draw()
	{
		Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<float>), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex<float>), (void*)(sizeof(float)*3));
		shader.setMat4("model", m_Model);
		glDrawArrays(GL_LINES, 0, 6);
		Unbind();
	}
    ~GuideLines()
	{
		if (m_IsConstructed)
			std::cout << "Guide Lines with Mesh ID: " << id << " has been destroyed.";
	}
};