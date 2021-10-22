#pragma once

#include "VertexBuffer.hpp"
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "ICallbacks.h"
#include "Ripple.hpp"
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
		Shader gerstener;
		std::shared_ptr<FPCamera> camera;
		std::shared_ptr<Plane> plane;
		std::shared_ptr<cuda::GerstnerWave> gwave;
		bool canToggle = false;
		bool isMouseEnabled = false;
		float timer = 0.0f;
	public:

		Simulation();
		void Update(const std::shared_ptr<bogong::Keyboard> &kbd,
					const std::shared_ptr<bogong::Mouse>& mouse, 
					GLFWwindow * glfwWindow, float delta) ;
		void Draw() const;
		void toggle(std::shared_ptr<Keyboard> kbd, std::shared_ptr<Mouse> mouse, float delta, GLFWwindow * window);
	};
}