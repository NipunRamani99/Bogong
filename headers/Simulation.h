#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Cube.h"
#include "Model.h"
#include "GuideLines.h"

class Simulation
{
private:
	GuideLines m_gl;
	Model obj;
	Shader m_Shader;
	Cube cube;
	float m_Scale = 0.895f;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		m_gl(glm::vec3(0.0f, 0.0f, 0.0f)),
		obj("assets/models/BMD-3/sprut.obj"),
		cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 0.2f)
	{
		m_Shader = p_Shader;
		m_gl.SetShader(m_Shader);
		obj.SetShader(m_Shader);
		obj.SetScale(glm::vec3(0.001f,0.001f,0.001f));
		m_Scale = 0.001f;
		cube.SetShader(m_Shader);
	}
	Simulation(Simulation && simulation)
	{
	
	}

	Simulation & operator=(Simulation&&p_Simulation)
	{
		m_Shader = p_Simulation.m_Shader;
		m_gl = std::move(p_Simulation.m_gl);
		obj = std::move(p_Simulation.obj);
		m_Scale = std::move(p_Simulation.m_Scale);
		cube = std::move(p_Simulation.cube);
		return *this;
	}
	void Begin()
	{
		
	}
	void Update()
	{
		if (ImGui::DragFloat("Scale: ", &m_Scale, 0.0001f, 0.0001, 1.0f))
		{
			obj.SetScale(glm::vec3(m_Scale, m_Scale, m_Scale));
		}
	}
	void Draw()
	{

		cube.Draw();
		m_gl.Draw();
		obj.Draw();
	}
};