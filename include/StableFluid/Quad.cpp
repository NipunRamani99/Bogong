#pragma once
#include "Quad.hpp"
#include "../Shaders.hpp"
#include "../Vertex.h"
#include "../Globals.h"
#include "../CudaTexture.hpp"
#include "StableFluidKernels.h"
using namespace bogong::cuda::StableFluid;

QuadMesh::QuadMesh()
{
	surf_height = 512;
	surf_width = 512;
	count = 4;
	Vertex<float> x1;
	x1.x = -1.f;
	x1.y = 1.f;
	x1.r = 1.0f;
	x1.g = 0.0f;
	x1.b = 0.0f;
	x1.a = 1.0f;
	x1.u = 0.0f;
	x1.v = 1.0f;
	Vertex<float> x2;
	x2.x = 1.0f;
	x2.y = 1.0f;
	x2.r = 1.0f;
	x2.g = 0.0f;
	x2.b = 0.0f;
	x2.a = 1.0f;
	x2.u = 1.0f;
	x2.v = 1.0f;
	Vertex<float> x3;
	x3.x = 1.0f;
	x3.y = -1.0f;
	x3.r = 1.0f;
	x3.g = 0.0f;
	x3.b = 0.0f;
	x3.a = 1.0f;
	x3.u = 1.0f;
	x3.v = 0.0f;
	Vertex<float> x4;
	x4.x = -1.0f;
	x4.y = -1.0f;
	x4.r = 1.0f;
	x4.g = 0.0f;
	x4.b = 0.0f;
	x4.a = 1.0f;
	x4.u = 0.0f;
	x4.v = 0.0f;
	std::vector<float4> textureSurf;
	textureSurf.resize(surf_width*surf_height);
	std::vector<Vertex<float>> vertices;
	vertices.push_back(x1);
	vertices.push_back(x2);
	vertices.push_back(x3);
	vertices.push_back(x4);
	vbo = std::make_shared<VertexBuffer>(vertices.data(), 4 * sizeof(Vertex<float>));
	VertexBufferLayout vbl;
	vbl.AddElement<float>(3);
	vbl.AddElement<float>(4);
	vbl.AddElement<float>(2);
	vbl.SetStride(sizeof(Vertex<float>));
	auto buffer1= std::make_pair(vbo, vbl);
	m_BufferVertex.push_back(buffer1);
	for (int x = 0; x < surf_width; x++)
	{
		for (int y = 0; y < surf_height; y++)
		{
			textureSurf[y * surf_width + x] = { 0.0f,0.0f,1.0f,1.0f };
		}
	}
	assert(!error());
	tex = std::make_shared<cuda::CudaTexture>(CudaTexture(textureSurf,surf_width,surf_height,GL_RGBA32F,GL_FLOAT,GL_TEXTURE_2D));
	assert(!error());
	m_TexVector.push_back(tex);
}

void QuadMesh::ProcessInput()
{
}

void QuadMesh::Update()
{
	tex->Map();
	tex->GetMappedPointer();
	cudaArray * p = tex->GetDataPtr();
	WashColor(p,surf_width,surf_height);
	tex->UnMap();
}

Quad::Quad()
{
	mesh	 = std::make_shared<QuadMesh>();
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
void Quad::Update(float t)
{
	mesh->Update();
}