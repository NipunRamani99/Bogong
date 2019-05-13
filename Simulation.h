#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "GuideLines.h"
#include "WaveMesh.h"
bool error()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::string error;
		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		std::cout << "GL_" << error.c_str();
		err = glGetError();
	}
	return true;
}
class Simulation
{
private:
	GuideLines m_gl;
	Shader m_Shader;
	WaveMesh wavemesh;
	float timer = 0.0f;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		m_gl(glm::vec3(0.0f,0.0f,0.0f)),
		wavemesh(300,300)
	{
		m_Shader = p_Shader;
		m_gl.SetShader(m_Shader);
		error();
		wavemesh.SetShader(m_Shader);
		error();
	}
	Simulation(Simulation && simulation)
	{
	    
	}
	Simulation & operator=(Simulation&&p_Simulation)
	{
		m_Shader = p_Simulation.m_Shader;
		m_gl = std::move(p_Simulation.m_gl);
		wavemesh = std::move(p_Simulation.wavemesh);
		return *this;
	}
	void Begin()
	{
		timer = 0.0f;
	}
	void Update()
	{
		timer += 0.001f;
		wavemesh.Update(timer);
		error();
	}
	void Draw()
	{
		//m_gl.Draw();
		wavemesh.Draw();
		error();
	}
};