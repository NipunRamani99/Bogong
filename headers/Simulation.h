#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ICallbacks.h"
#include "../Lines.hpp"


class Simulation
{
private:

	Shader m_Shader;
	Lines line;
	Lines line2;
	Lines line3;
	float m_Scale = 0.895f;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		line(glm::vec3(-100.0f,0.0f,0.0f),glm::vec3(100.0f,0.0f,0.0f)),
		line2(glm::vec3(0.0f,-100.0f,0.0f),glm::vec3(0.0f,100.0f,0.0f)),
	    line3(glm::vec3(0.0f,0.0f,-100.0f),glm::vec3(0.0f,0.0f,100.0f))
	{  
		m_Shader      = p_Shader;
		m_Scale       = 0.001f;
		ICallbacks::SetShader(m_Shader);
		line.SetShader(m_Shader);
		line2.SetShader(m_Shader);
		line3.SetShader(m_Shader);
	}
	Simulation(Simulation && simulation)
	{
		m_Shader = std::move(simulation.m_Shader);
		m_Scale = std::move(simulation.m_Scale);
		line = std::move(simulation.line);
		line2 = std::move(simulation.line2);
		line3 = std::move(simulation.line3);
	}

	Simulation & operator=(Simulation&&p_Simulation)
	{
		m_Shader = p_Simulation.m_Shader;
		m_Scale = std::move(p_Simulation.m_Scale);
		line  = std::move(p_Simulation.line);
		line2 = std::move(p_Simulation.line2);
		line3 = std::move(p_Simulation.line3);
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
		line.Draw();
		line2.Draw();
		line3.Draw();
		error();
	}
};