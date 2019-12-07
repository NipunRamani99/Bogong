#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "../include/GerstenerWave.hpp"

bogong::cuda::GerstnerWaveMesh::GerstnerWaveMesh(int rows, float width):
	rows(rows),
	width(width)
{
	meshprop.mesh_height = rows;
	meshprop.mesh_width = rows;
	makeMesh();
	makeVBO();
	makeLayout();
	makeIndicesLines();
	makeIBO();
	m_BufferVertex.push_back(std::make_pair(std::dynamic_pointer_cast<VertexBuffer>(vertex_cvbo), layout1));
	m_BufferVertex.push_back(std::make_pair(std::dynamic_pointer_cast<VertexBuffer>(color_cvbo), layout2));
	m_BufferVertex.push_back(std::make_pair(std::dynamic_pointer_cast<VertexBuffer>(normals_cvbo), layout3));
	props[0].amplitude = 0.001f;
	props[1].amplitude = 0.004f;
	props[2].amplitude = 0.004f;
	props[3].amplitude = 0.002f;
	props[0].isCircular = 0;
	props[1].isCircular = 0xFF;
	props[2].isCircular = 0xFF;
	props[3].isCircular = 0;
	props[0].dirx = 1.0f / sqrtf(2);
	props[0].diry = 1.0f / sqrtf(2);
	props[1].x = 0.5f;
	props[1].y = 0.1f;
	props[2].x = 0.1f;
	props[2].y = 0.3f;
	props[3].dirx = 0.0f;
	props[3].diry = 1.0f;
	props[0].w = props[1].w = props[2].w = props[3].w = 1.0f;
	props[3].q = 1.0f;
	n = 4;
}


void bogong::cuda::GerstnerWaveMesh::ReadInputs()
{
	for (int i = 0; i < n; i++)
	{
		std::string label = "Q" + std::to_string(i);
		ImGui::InputFloat(label.c_str(), &props[i].q, 0.001f, 0.001f, 5);
	}
	for (int i = 0; i < n; i++)
	{
		std::string label = "Amplitude" + std::to_string(i);
		ImGui::InputFloat(label.c_str(), &props[i].amplitude, 0.001f, 0.001f, 5);
	}
	for (int i = 0; i < n; i++)
	{
		std::string label = "Phase" + std::to_string(i);
		ImGui::InputFloat(label.c_str(), &props[i].phase, 0.001f, 0.001f, 5);
	}
	for (int i = 0; i < n; i++)
	{
		std::string label = "Wave velocity " + std::to_string(i);
		ImGui::InputFloat(label.c_str(), &props[i].w, 0.001f, 0.001f, 5);
	}
	for (int i = 0; i < n; i++)
	{
		std::string labl = "Flag " + std::to_string(i);
		ImGui::InputInt(labl.c_str(), &props[i].isCircular, 0);
		if (props[i].isCircular == 0xFF)
		{
			std::string label = "Vec2 " + std::to_string(i);
			ImGui::InputFloat2(label.c_str(), &props[i].x, 4);
		}
		else
		{
			std::string label = "DirX/Y " + std::to_string(i);
			ImGui::InputFloat2(label.c_str(), &props[i].dirx, 4);
		}
	}
}

void bogong::cuda::GerstnerWaveMesh::Update(float time)
{
	counter += time;
	vertex_cvbo->Map();
	vertex_cvbo->GetMappedPointer();
	normals_cvbo->Map();
	normals_cvbo->GetMappedPointer();

	GerstnerNormalTest(vertex_cvbo->GetData(), normals_cvbo->GetData(), props, meshprop, n, counter);
	vertex_cvbo->UnMap();
	normals_cvbo->UnMap();
	color_cvbo->Map();
	color_cvbo->GetMappedPointer();
	UpdateColors(color_cvbo->GetData(), rows, rows, 2.5f * counter);
	color_cvbo->UnMap();
}

void bogong::cuda::GerstnerWaveMesh::Amplitude(float amplitude)
{
	this->amplitude = amplitude;
}

void bogong::cuda::GerstnerWaveMesh::makeLayout()
{
	layout1.AddElement<float>(3);
	layout2.AddElement<float>(4);
	layout3.AddElement<float>(3);
}

void bogong::cuda::GerstnerWaveMesh::makeVBO()
{
	vertex_cvbo = std::make_shared<CudaVBO<float3>>(vertices);
	color_cvbo = std::make_shared<CudaVBO<float4>>(colors);
	normals_cvbo = std::make_shared<CudaVBO<float3>>(vertices.size() * sizeof(float3));
}

void bogong::cuda::GerstnerWaveMesh::makeIBO()
{
	m_IBO = bogong::IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));
}

void bogong::cuda::GerstnerWaveMesh::makeIndicesQuads()
{
	unsigned int idx = 0;

	for (int j = 0; j < rows - 1; j++)
	{
		for (int i = 0; i < rows - 1; i++)
		{
			indices.push_back(idx);
			indices.push_back(idx + rows);
			indices.push_back(idx + rows + 1);
			indices.push_back(idx + 1);
			idx++;
		}
		idx++;
	}
	count = indices.size();
}

void bogong::cuda::GerstnerWaveMesh::makeIndicesLines()
{
	unsigned int idx = 0;

	for (int j = 0; j < rows - 1; j++)
	{
		for (int i = 0; i < rows - 1; i++)
		{
			indices.push_back(idx);
			indices.push_back(idx + 1);
			indices.push_back(idx);
			indices.push_back(idx + rows);
			indices.push_back(idx + 1);
			indices.push_back(idx + rows + 1);
			indices.push_back(idx + rows);
			indices.push_back(idx + rows + 1);
			indices.push_back(idx + rows);
			indices.push_back(idx + 1);
			idx++;
		}
		idx++;
	}
	count = indices.size();
}

void bogong::cuda::GerstnerWaveMesh::makeMesh()
{
	vertices.resize(rows * rows);
	colors.resize(rows * rows);
	float delX = width / (float)rows;
	float delZ = delX;
	unsigned int idx = 0;
	for (int x = 0; x < rows; x++)
	{
		for (int z = 0; z < rows; z++)
		{
			vertices[idx] = makeVertex(x, z, delX, delZ);
			colors[idx] = makeColor();
			idx++;
		}
	}
	count = rows * rows;
}

float3 bogong::cuda::GerstnerWaveMesh::makeVertex(int x, int z, float delX, float delZ)
{
	float3 vertex;
	vertex.x = float(x) * delX - width / 2.0f;
	vertex.z = float(z) * delZ - width / 2.0f;
	float freq = 1.5f;
	vertex.y = 0.0f; //sin(vertex.x*freq) + cos(vertex.z*freq);
	return vertex;
}

float4 bogong::cuda::GerstnerWaveMesh::makeColor()
{
	float4 color;
	color.x = 1.0f;
	color.y = 0.0f;
	color.z = 0.0f;
	color.w = 1.0f;
	return color;
}
