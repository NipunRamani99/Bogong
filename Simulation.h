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
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		m_gl(glm::vec3(0.0f,0.0f,0.0f))
	{
		m_Shader = p_Shader;
		m_gl.SetShader(m_Shader);
	}
	Simulation(Simulation && simulation)
	{
	
	}
	Simulation & operator=(Simulation&&p_Simulation)
	{
		m_Shader = p_Simulation.m_Shader;
		m_gl = std::move(p_Simulation.m_gl);
		return *this;
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