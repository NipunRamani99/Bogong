#pragma once

#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
#include "Lines.hpp"
#include "Ripple.hpp"
#include "WaveMeshTest.h"
namespace bogong {
	class Simulation
	{
	private:

		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader m_RiplShader;
		cuda::Wave wave;
		float m_Scale = 0.895f;
		float time = 0.01;
	public:
		Simulation() = default;
		Simulation(Shader p_Shader)
			:
			wave(100)
		{
			m_Shader = p_Shader;
			m_Scale = 0.001f;
			m_RiplShader.LoadShader("VertexShaderRipple.glsl", ShaderType::VERTEX);
			m_RiplShader.LoadShader("FragmentShaderRipple.glsl", ShaderType::FRAGMENT);
			m_RiplShader.LoadProgram();
			error();
			ICallbacks::AddShader(m_RiplShader);
			ICallbacks::SetShader(m_Shader);
			wave.SetShader(m_Shader);
			error();
		}
		Simulation(Simulation && simulation)
		{
			m_Shader = std::move(simulation.m_Shader);
			m_RiplShader = std::move(simulation.m_RiplShader);
			wave = std::move(simulation.wave);
			time = simulation.time;
		}

		Simulation & operator=(Simulation&&p_Simulation)
		{
			m_Shader = p_Simulation.m_Shader;
			m_RiplShader = std::move(p_Simulation.m_RiplShader);
			wave = std::move(p_Simulation.wave);
			time = p_Simulation.time;
			return *this;
		}
		void Begin()
		{

		}
		void Update()
		{
			wave.Test(time);
			time += 0.01;
		}
		void Draw()
		{
			wave.Draw();
			error();
		}
	};
}