#pragma once
#include "Model.h"
class Cube : public Model
{
	glm::vec4 m_Color  =  glm::vec4(1.0f,1.0f,0.666f,1.0f);
public:
	Cube()
	{
	
	}
	Cube(glm::vec3 p_Position, glm::vec4 p_Color, float p_Length)
	{
		m_Color = p_Color;
		float xlength = p_Length;
		float ylength = p_Length;
		float zlength = p_Length;
		Vertex<float> vertA;
		Vertex<float> vertB;
		Vertex<float> vertC;
		Vertex<float> vertD;
		Vertex<float> vertE;
		Vertex<float> vertF;
		Vertex<float> vertG;
		Vertex<float> vertH;
		unsigned int indices[] = { 0,2,1,
								   1,2,3,
		                           4,5,6,
		                           7,6,5,
								   1,7,5,
								   1,3,7,
								   0,1,4,
								   1,5,4,6,7,2,7,3,2,0,4,2,4,6,2};
		int count = sizeof(indices) / sizeof(unsigned int);
		std::vector<unsigned int> vecIndices(indices, indices + count);

		//(0,0,0)
		vertA = CreateVertex<float>(glm::vec3(-xlength / 2, -ylength / 2, -zlength / 2), p_Color, glm::vec2(0, 0));

		//(1,0,0)
		vertB = CreateVertex<float>(glm::vec3(xlength / 2, -ylength / 2, -zlength / 2), p_Color, glm::vec2(0, 0));

		//(0,1,0)
		vertC = CreateVertex<float>(glm::vec3(-xlength / 2, ylength / 2, -zlength / 2), p_Color, glm::vec2(0, 0));

		//(1,1,0)
		vertD = CreateVertex<float>(glm::vec3(xlength / 2, ylength / 2, -zlength / 2), p_Color, glm::vec2(0, 0));

		//(0,0,1)
		vertE = CreateVertex<float>(glm::vec3(-xlength / 2, -ylength / 2, zlength / 2), p_Color, glm::vec2(0, 0));

		//(1,0,1)
		vertF = CreateVertex<float>(glm::vec3(xlength / 2, -ylength / 2, zlength / 2), p_Color, glm::vec2(0, 0));

		//(0,1,1)
		vertG = CreateVertex<float>(glm::vec3(-xlength / 2, ylength / 2, zlength / 2), p_Color, glm::vec2(0, 0));

		//(1,1,1)
		vertH = CreateVertex<float>(glm::vec3(xlength / 2, ylength / 2, zlength / 2), p_Color, glm::vec2(0, 0));

		Vertex<float>  GuideVertex[] = { vertA,vertB,vertC,vertD,vertE,vertF,vertG,vertH };
		std::vector<Vertex<float>> vertices(GuideVertex, GuideVertex + 8);
		m_Meshes.push_back(std::move(Mesh(p_Position)));
		m_Meshes[0].SetVertices(std::move(vertices));
		m_Meshes[0].SetIndices(std::move(vecIndices));
		m_Meshes[0].SetDrawMode(GL_TRIANGLES);
	}
};

//0, 1, 2,
//0, 3, 2,
//4, 6, 5,
//6, 7, 5,
//7, 5, 1,
//1, 7, 3,
//4, 6, 0,
//6, 2, 0,
//4, 5, 1,
//1, 5, 0,
//2, 3, 7,
//6, 7, 2
//* /