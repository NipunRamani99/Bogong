#pragma once
#include<vector>
#include<glm/gtx/transform.hpp>
#include "Vertex.h"
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Texture.h"
#include "IndexBuffer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
protected:
	std::vector<Vertex<float>>  m_Vertices;
	std::vector<unsigned int>   m_Indices;
	glm::vec3 m_Position=glm::vec3(0.0f,0.0f,0.0f);
	glm::mat4 m_Model = glm::mat4(1.0f);
	std::string id = "";
	bool m_IsConstructed = false;
public:
	Model()
	{
		m_IsConstructed = false;
	}
	Model(Model && p_Model)
	{
		p_Model.m_IsConstructed = false;
		m_Vertices = std::move(p_Model.m_Vertices);
		m_Indices = std::move(p_Model.m_Indices);
		m_Position = p_Model.m_Position;
		m_Model = p_Model.m_Model;
		id = p_Model.id;
		
	}
	Model(std::vector<Vertex<float>> & p_Vertices, std::vector<unsigned int> & p_Indices)
	{
		m_Vertices = p_Vertices;
		m_Indices = p_Indices;
		id = GenerateRandomString(10);
		m_IsConstructed = true;
	}
	Model(glm::vec3 p_Position)
	{
		m_Position = p_Position;
		m_Model = glm::translate(m_Model, m_Position);
		id = GenerateRandomString(10);
		m_IsConstructed = true;
	}
    virtual ~Model()
	{
		if (m_IsConstructed)
			std::cout << "Model ID: " << id << " has been destroyed.";
	}
	void SetPosition(glm::vec3 p_Position)
	{
		m_Position = p_Position;
		m_Model = glm::mat4(1.0f);
		
	}
	void SetVertices(std::vector<Vertex<float>> & p_Vertices)
	{
		m_Vertices = p_Vertices;
	}
	void SetVertices(std::vector<unsigned int> & p_Indices)
	{
		m_Indices = p_Indices;
	}
	void ImportModel(std::string p_Path)
	{
		Assimp::Importer importer;
		const aiScene * scene = importer.ReadFile(p_Path, aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);
		if (!scene)
		{
			std::cout << "Error.";

		}
	}
private:
	std::string GenerateRandomString(int p_NumChars)
	{
		std::string str="";
		long long seed = std::chrono::steady_clock::now().time_since_epoch().count();
		std::default_random_engine rd((unsigned int)seed);
		std::uniform_int_distribution<int> intDist(0,26);
		for (int i = 0; i < p_NumChars;i++)
		{
			str += 'A' + (char)intDist(rd);
		}
		return str;
		
	}
	
};