#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Lights.hpp"
#include "Cube.h"
#include "Model.h"
#include "GuideLines.h"
#include "Camera.h"
#include "Cube_norm.h"
#include "Globals.h"


class Simulation
{
private:

	GuideLines m_gl;
	Shader m_Shader;
	float m_Scale = 0.895f;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		m_gl(glm::vec3(0,0,0))
	{  
		m_Shader      = p_Shader;
		m_Scale       = 0.001f;
		m_gl.SetShader(m_Shader);
		ICallbacks::SetShader(m_Shader);
	}
	Simulation(Simulation && simulation)
	{
		m_gl     = std::move(simulation.m_gl);  
		m_Shader = std::move(simulation.m_Shader);
		m_Scale = std::move(simulation.m_Scale);
	}

	Simulation & operator=(Simulation&&p_Simulation)
	{
		m_gl     = std::move(p_Simulation.m_gl);
		m_Shader = p_Simulation.m_Shader;
		m_Scale = std::move(p_Simulation.m_Scale);
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