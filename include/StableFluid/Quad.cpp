#pragma once
#include "Quad.hpp"
#include "../Shaders.hpp"
using namespace bogong::cuda::StableFluid;
QuadMesh::QuadMesh()
{
	
	count = 4;
	Vertex<float> x1;
	x1.x = -1.f;
	x1.y = 1.f;
	x1.r = 1.0f;
	x1.g = 0.0f;
	x1.b = 0.0f;
	x1.a = 1.0f;

	Vertex<float> x2;
	x2.x = 1.0f;
	x2.y = 1.0f;
	x2.r = 1.0f;
	x2.g = 0.0f;
	x2.b = 0.0f;
	x2.a = 1.0f;
	
	Vertex<float> x3;
	x3.x = 1.0f;
	x3.y = 1.0f;
	x3.r = 1.0f;
	x3.g = 0.0f;
	x3.b = 0.0f;
	x3.a = 1.0f;

	Vertex<float> x4;
	x4.x = 1.0f;
	x4.y = 1.0f;
	x4.r = 1.0f;
	x4.g = 0.0f;
	x4.b = 0.0f;
	x4.a = 1.0f;

	std::vector<Vertex<float>> vertices;
	vertices.push_back(x1);
	vertices.push_back(x2);
	vertices.push_back(x3);
	vertices.push_back(x4);
	vbo = std::make_shared<VertexBuffer>(vertices.data(), 4 * sizeof(Vertex<float>));
	VertexBufferLayout vbl;
	vbl.AddElement<float>(3);
	vbl.AddElement<float>(4);
	auto buffer1= std::make_pair(vbo, vbl);
	m_BufferVertex.push_back(buffer1);

}

void QuadMesh::ProcessInput()
{
}

void QuadMesh::Update()
{
}

Quad::Quad()
{
	mesh = std::make_shared<QuadMesh>();
	renderer = std::make_shared<CudaRenderer>();
	renderer->BindBuffer(mesh);
	renderer->SetDrawMode(GL_QUADS);
}

void Quad::SetShader(bogong::Shader shader)
{
	renderer->SetShader(shader);
}

void Quad::Draw()
{
	renderer->RenderMesh(mesh);
}
