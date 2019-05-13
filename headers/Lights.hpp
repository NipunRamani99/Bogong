#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glm/gtx/transform.hpp>
class LightSource
{
private:
	glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 m_Position = glm::vec3(1.0f, 1.0f, 1.0f);
public:
	LightSource(LightSource && p_LightSource)
	{

	}
	
};