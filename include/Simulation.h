#pragma once
#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
#include "Ripple.hpp"
#include "WaveMeshTest.h"
#include "LineGrid.hpp"
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "Plane.hpp"
namespace bogong{
	class Simulation
	{
	private:
		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		std::shared_ptr<FPCamera> camera;
		std::shared_ptr<Plane> plane;
	public:
		
		Simulation()
		{
			m_Shader.LoadShader("shaders/BasicVertexShader.glsl", bogong::ShaderType::VERTEX);
			m_Shader.LoadShader("shaders/BasicFragmentShader.glsl", bogong::ShaderType::FRAGMENT);
			m_Shader.LoadProgram();
			assert(!error());

			plane = std::make_shared<Plane>();
			plane->setShader(m_Shader);
			assert(!error());

			camera = std::make_shared<FPCamera>();
			assert(!error());

		}
		void Update(bogong::Keyboard & kbd, bogong::Mouse & mouse,float delta)
		{
			m_Shader.Bind();
			camera->Update(kbd, mouse,delta);
			m_Shader.setMat4("projection", camera->GetProjection());
			assert(!error());

			m_Shader.setMat4("view", camera->GetView());
			assert(!error());

		}
		void Draw() const
		{
			assert(!error());

			plane->Draw();
			assert(!error());

		}
	};
}