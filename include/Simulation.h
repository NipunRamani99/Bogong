#pragma once

#include "Shaders.hpp"

#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include "Plane.hpp"
#include "Camera.h"
#include "Heat2D/HeatQuad.hpp"
namespace bogong{
	class Simulation
	{
	private:
		glm::vec3 lightPos = glm::vec3(-1.0f, 0.2f, 0.0f);
		Shader m_Shader;
		Shader quad_shader;
		std::shared_ptr<FPCamera> camera;
		std::shared_ptr<cuda::Heat2D::Quad> quad;
	public:

		Simulation();
		void Update(const std::shared_ptr<bogong::Keyboard> &kbd,const std::shared_ptr<bogong::Mouse>& mouse, float delta) ;
		void Draw() const;
	};
}

