#pragma once

#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
//#include "Ripple.hpp"
#include "WaveMeshTest.h"
namespace bogong {
	class Simulation
	{
	private:

		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader m_RiplShader;
		cuda::Wave wave;
		float t=0.0f;
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
			error();
			ICallbacks::SetShader(m_Shader);
			wave.SetShader(m_Shader);
			error();
		}
		/*Simulation(Simulation && simulation)
		{
			m_Shader = std::move(simulation.m_Shader);
			m_RiplShader = std::move(simulation.m_RiplShader);
			time = simulation.time;
			ripple = std::move(simulation.ripple);
		}

		Simulation & operator=(Simulation&&p_Simulation)
		{
			m_Shader = p_Simulation.m_Shader;
			m_RiplShader = std::move(p_Simulation.m_RiplShader);
			time = p_Simulation.time;
			ripple = std::move(p_Simulation.ripple);
			return *this;
		}*/
		void Begin()
		{
		}
		void Update()
		{
			
			wave.Update(t);
			t += 0.005;
		}
		void Draw()
		{
			wave.Draw();
			error();
		}
	};
}