#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "GuideLines.h"
#include "WaveMesh.h"
class Simulation
{
private:
	GuideLines m_gl;
	Shader m_Shader;
	WaveMesh wavemesh;
	float timer = 0.0f;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		m_gl(glm::vec3(0.0f,0.0f,0.0f)),
		wavemesh(300,300)
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
		wavemesh = std::move(p_Simulation.wavemesh);
		return *this;
	}
	void Begin()
	{
		timer = 0.0f;
	}
	void Update()
	{
		timer += 0.001f;
		wavemesh.Update(timer);

	}
	void Draw()
	{
		m_gl.Draw();
		wavemesh.Draw();
	}
};