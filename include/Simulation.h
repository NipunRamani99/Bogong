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
		
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		float cameraSpeed = 1.0f;
		int screenWidth = 800;
		int screenHeight = 600;
		float prevMouseX = 0.0f;
		float prevMouseY = 0.0f;
		float currMouseX = 0.0f;
		float currMouseY = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
	public:

		Simulation();
		void Update(const std::shared_ptr<bogong::Keyboard> &kbd,const std::shared_ptr<bogong::Mouse>& mouse, float delta) ;
		void Draw() const;
	};
}