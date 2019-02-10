#pragma once
#include "Init.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	//Creating Shaders
	GLuint vertexShadID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShadID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

	if (VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();

	}
	else
	{
		Init::LogError("Impossible to open vertexshader.");
		return 0;
	}
	//Reading the fragment shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int infoLogLength;

	//Compiling Vertex Shader
	std::cout << "Compiling shader: " + std::string(vertex_file_path) + " \n";
	const char * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShadID, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShadID);


	glGetShaderiv(vertexShadID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShadID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> error(infoLogLength + 1);
		glGetShaderInfoLog(vertexShadID, infoLogLength, NULL, &error[0]);
		Init::LogError(std::string(&error[0]));
	}

	std::cout << "Compiling FragShaders: " + std::string(fragment_file_path) + "\n";
	char const * fragSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragmentShadID, 1, &fragSourcePointer, NULL);
	glCompileShader(fragmentShadID);

	glGetShaderiv(fragmentShadID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShadID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> error(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShadID, infoLogLength, NULL, &error[0]);
		Init::LogError(std::string(&error[0]));
	}


	//Link the program
	std::cout << "Linking the program.\n";
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShadID);
	glAttachShader(ProgramID, fragmentShadID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> error(infoLogLength + 1);
		glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &error[0]);
		Init::LogError(std::string(&error[0]));
	}

	glDetachShader(ProgramID, vertexShadID);
	glDetachShader(ProgramID, fragmentShadID);

	glDeleteShader(vertexShadID);
	glDeleteShader(fragmentShadID);
	return ProgramID;
}