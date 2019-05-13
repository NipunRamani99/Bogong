#pragma once
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Lights.hpp"
#include "Cube.h"
#include "Model.h"
#include "GuideLines.h"
#include "Camera.h"
#include "Cube_norm.h"
#include "Globals.h"
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
	Shader m_LightShader;
	Shader m_CubeShader1;
	Shader m_CubeNormShader;
	LightSource m_Light;
	float m_Scale = 0.895f;
	Cube cube;
	Cube_norm cuben;
public:
	Simulation() = default;
	Simulation(Shader p_Shader)
		:
		cuben(glm::vec3(0.0f,0.0f,0.0f),glm::vec4(1.0f,0.5f,0.0f,1.0f),1.0f)
	{  

		m_Shader      = p_Shader;
		m_Scale       = 0.001f;
		/*m_LightShader.LoadShader("VertexShaderLight.glsl", ShaderType::VERTEX);
		m_LightShader.LoadShader("LightFragmentShader.glsl", ShaderType::FRAGMENT);
		m_LightShader.LoadProgram();
		error();
		m_CubeShader1.LoadShader("vertexShader.glsl", ShaderType::VERTEX);
		m_CubeShader1.LoadShader("fragmentShader.glsl", ShaderType::FRAGMENT);
		m_CubeShader1.LoadProgram();
		error();*/
		m_CubeNormShader.LoadShader("vertexShader(N).glsl",   ShaderType::VERTEX);
		m_CubeNormShader.LoadShader("fragmentShader(N).glsl", ShaderType::FRAGMENT);
		m_CubeNormShader.LoadProgram();
		m_CubeNormShader.Bind();
		m_CubeNormShader.setVec3("lightColor", glm::vec3(1.0f,1.0f,1.0f));
		m_CubeNormShader.setVec3("lightPos", glm::vec3(0.75f, 0.75f, 0.75f));
		error();
		cuben.SetShader(m_CubeNormShader);
		error();
		ICallbacks::AddShader(m_CubeNormShader);
		error();
		ICallbacks::AddShader(m_Shader);
		error();
		/*m_CubeShader1.Bind();
		m_CubeShader1.setVec3("lightColor", glm::vec3(1.0f,1.0f,1.0f));
		p_Shader.Bind();
		error();
		ICallbacks::AddShader(m_LightShader);
		error();
		ICallbacks::AddShader(m_CubeShader1);
		error();
		m_gl.SetShader(m_Shader);
		error();
		m_Light.SetShader(m_LightShader);
		error();
		ICallbacks::SetShader(m_Shader);
		error();
		cube.SetShader(m_CubeShader1);*/
	}
	Simulation(Simulation && simulation)
	{
		//m_gl     = std::move(simulation.m_gl);
		//m_Light  = std::move(simulation.m_Light);
		//m_Scale  = std::move(simulation.m_Scale);
		//m_LightShader = std::move(simulation.m_LightShader);
		//m_CubeShader1 = std::move(simulation.m_CubeShader1);
		//cube = std::move(simulation.cube);
		cuben = std::move(simulation.cuben);
		m_CubeNormShader = std::move(simulation.m_CubeNormShader);

		m_Shader = std::move(simulation.m_Shader);
		m_Scale = std::move(simulation.m_Scale);
	}

	Simulation & operator=(Simulation&&p_Simulation)
	{
		/*
		m_gl     = std::move(p_Simulation.m_gl);
		m_Scale  = std::move(p_Simulation.m_Scale);
		m_Light  = std::move(p_Simulation.m_Light);
		m_LightShader = std::move(p_Simulation.m_LightShader);
		m_CubeShader1 = std::move(p_Simulation.m_CubeShader1);
		cube = std::move(p_Simulation.cube);*/
		cuben = std::move(p_Simulation.cuben);
		m_CubeNormShader = std::move(p_Simulation.m_CubeNormShader);
		m_Shader = p_Simulation.m_Shader;
		m_Scale = std::move(p_Simulation.m_Scale);
		return *this;
	}
	void Begin()
	{
		
	}
	void Update()
	{
		
	}
	void Draw()
	{
		cuben._Draw();
		m_CubeNormShader.setVec3("viewPos", Globals::viewPos);
		m_Shader.Bind();
		error();
/*
		m_Light.Apply();
		
		cube.Draw();*/
	}
};