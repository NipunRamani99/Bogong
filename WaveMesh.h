#pragma once
#include "VertexArray.hpp"
#include "CudaVBO.h"
#include "Shaders.hpp"
#include "RunKernel.h"
class WaveMesh
{
private:
	Shader m_Shader;
	VertexArray m_VAO;
	CudaVBO<float4> m_VBO;
	VertexBuffer m_ColorVBO;
	int m_Width = 0;
	int m_Height = 0;
	float4 * color;
public:
	WaveMesh() = default;
	WaveMesh(int width, int height)
	{
		m_Width = width;
		m_Height = height;
		color = new float4[width * height];
		for (int i = 0; i < width*height; i++)
		{
			color[i].x = 1.0f;
			color[i].y = 0.0f;
			color[i].z = 0.0f;
			color[i].w = 1.0f;
		}
		m_VAO = VertexArray();
		m_VBO = CudaVBO<float4>(m_Width*m_Height*sizeof(float4));
		m_ColorVBO = VertexBuffer(color, m_Width * m_Height * sizeof(float4));
	}
	void SetShader(Shader p_Shader)
	{
		m_Shader = p_Shader;
		m_Shader.setBool("isTextured", false);

	}
	void Draw()
	{
		m_VAO.Bind();
		m_VBO.Bind();
		m_Shader.Bind();
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float4), (void*)0);
		m_ColorVBO.Bind();
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float4), (void*)(0));
		glDrawArrays(GL_POINTS, 0, m_Width*m_Height);
		m_ColorVBO.Unbind();
		m_VAO.Unbind();
	}
	void Update(float time)
	{
		m_VBO.Map();
		m_VBO.GetMappedPointer();
		UpdateMesh(m_VBO.GetData(), m_Width, m_Height, time);
		m_VBO.UnMap();
	}

};