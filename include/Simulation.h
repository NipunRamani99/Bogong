#pragma once

#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
#include "Lines.hpp"
#include "Ripple.hpp"
#include "SurfaceWave/WaveMesh.hpp"
namespace bogong {
	class Simulation
	{
	private:

		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader m_RiplShader;
		cuda::Wave wave;
		bogong::Ripple ripple;
		float m_Scale = 0.895f;
		float time = 0.01;
	public:
		Simulation() = default;
		Simulation(Shader p_Shader)
			:
			ripple(glm::vec3(0.0f,0.0f,0.0f),1.0f)
		{
			m_Shader = p_Shader;
			m_Scale = 0.001f;
			m_RiplShader.LoadShader("shaders/VertexShaderRipple.glsl", ShaderType::VERTEX);
			m_RiplShader.LoadShader("shaders/FragmentShaderRipple.glsl", ShaderType::FRAGMENT);
			m_RiplShader.LoadProgram();
			error();
			m_RiplShader.Bind();
			m_RiplShader.setVec3("lightLocation", lightPos);
			ICallbacks::AddShader(m_RiplShader);
			ICallbacks::SetShader(m_Shader);
			wave.SetShader(m_Shader);
			ripple.SetShader(m_RiplShader);
			error();
		}
		Simulation(Simulation && simulation)
		{
			m_Shader = std::move(simulation.m_Shader);
			m_RiplShader = std::move(simulation.m_RiplShader);
			wave = std::move(simulation.wave);
			time = simulation.time;
			ripple = std::move(simulation.ripple);
		}

		Simulation & operator=(Simulation&&p_Simulation)
		{
			m_Shader = p_Simulation.m_Shader;
			m_RiplShader = std::move(p_Simulation.m_RiplShader);
			wave = std::move(p_Simulation.wave);
			time = p_Simulation.time;
			ripple = std::move(p_Simulation.ripple);
			return *this;
		}
		void Begin()
		{
		}
		void Update()
		{
			if (::ImGui::DragFloat3("Light Pos", (float*)&lightPos))
			{
				m_RiplShader.Bind();
				m_RiplShader.setVec3("lightLocation",lightPos);
			}
		}
		void Draw()
		{
			ripple.Draw();
			error();
		}
	};
}