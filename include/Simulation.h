#pragma once
#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
#include "Ripple.hpp"
#include "WaveMeshTest.h"
#include "LineGrid.hpp"
#include <memory>
#include "Imgui.h"

namespace bogong{
	class Simulation
	{
	private:
		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader m_RiplShader;
		std::shared_ptr<cuda::LineGrid> lineGrid;
		float t = 0.0f;
		float m_Scale = 0.895f;
		float time = 0.01;
		float speed = 0.0005f;
		float amplitude = 1.0f;
	public:
		Simulation() = default;
		Simulation(Shader p_Shader)
		{
			m_Shader = p_Shader;
			lineGrid = std::make_shared<cuda::LineGrid>(64,10);
			error();
			ICallbacks::SetShader(m_Shader);
			lineGrid->SetShader(m_Shader);
			error();
		}
		void Update()
		{
			lineGrid->Input();
			lineGrid->Update(time);
			ImGui::InputFloat("Wave speed.", &speed, 0.0001, 7);
			time += speed;
			if (ImGui::InputFloat("Wave Amplitude.", &amplitude, 0.0001, 7))
			{
				lineGrid->SetAmplitude(amplitude);
			}
		}
		void Draw()
		{
			lineGrid->Draw();
			error();
		}
	};
}