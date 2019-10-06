#pragma once

#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
//#include "Ripple.hpp"
#include "WaveMeshTest.h"
#include "LineGrid.hpp"
#include <memory>
namespace bogong {
	class Simulation
	{
	private:

		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader m_RiplShader;
		std::shared_ptr<cuda::LineGrid> lineGrid;
		float t=0.0f;
		float m_Scale = 0.895f;
		float time = 0.01;
	public:
		Simulation() = default;
		Simulation(Shader p_Shader)
		{
			m_Shader = p_Shader;
			lineGrid = std::make_shared<cuda::LineGrid>(128,5);
			error();
			ICallbacks::SetShader(m_Shader);
			lineGrid->SetShader(m_Shader);
			
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
			lineGrid->Update(time);
			time += 0.0005f;
		}
		void Draw()
		{
			lineGrid->Draw();
			error();
		}
	};
}