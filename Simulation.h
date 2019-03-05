#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include "GuideLines.h"
class Simulation
{
private:
	GuideLines m_gl;
	Shader m_Shader;
public:
	Simulation()
	{
	
	}
	Simulation(Shader p_Shader)
	{
		m_Shader = p_Shader;
		m_gl = GuideLines(glm::vec3(0.0f, 0.0f, 0.0f));
		m_gl.SetShader(m_Shader);
	}
	void Begin()
	{
		
	}
	void Update()
	{


	}
	void Draw()
	{
		m_gl.Draw();
	}
};