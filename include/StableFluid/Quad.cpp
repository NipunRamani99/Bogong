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
	surf_height = 1024;
	surf_width = 512;
	count = 6;
	float vertices[] = { -1.0f,-1.0f,0.0f, 0.0f,0.0f,
					 -1.0f,1.0f,0.0f,  0.0f,1.0f,
					  1.0f,1.0f,0.0f,  1.0f,1.0f,

					 1.0f,-1.0f,0.0f, 1.0f,0.0f,
					 1.0f,1.0f,0.0f,  1.0f,1.0f,
					-1.0f,-1.0f,0.0f, 0.0f,0.0f
	};
	std::vector<float4> textureSurf;
	textureSurf.resize(surf_width*surf_height);
	size_t vertSize = sizeof(vertices);
	vbo = std::make_shared<VertexBuffer>(vertices, vertSize);
	VertexBufferLayout vbl;  
	vbl.AddElement<float>(3);
	vbl.AddElement<float>(2);
	auto buffer1= std::make_pair(vbo, vbl);
	m_BufferVertex.push_back(buffer1);
	for (int x = 0; x < surf_width; x++)
	{
		for (int y = 0; y < surf_height; y++)
		{
			size_t offset = y * surf_width + x;
			textureSurf[offset].x = (float)x / (float)surf_width;
			textureSurf[offset].y = 0.5f + 0.5f * cos(3.14592*y / 180.0f + 4);
			textureSurf[offset].z = textureSurf[y * surf_width + x].x;
			textureSurf[offset].w = 1.0f;
		}
	}
	assert(!error());
	tex = std::make_shared<cuda::CudaTexture>(textureSurf,surf_width,surf_height,GL_RGBA32F,GL_FLOAT,GL_TEXTURE_2D);
	assert(!error());
	m_TexVector.push_back(tex);
}

void QuadMesh::ProcessInput()
{
}

void QuadMesh::Update(float delT)
{
	tex->Map();
	tex->GetMappedPointer();
	cudaArray_t p = tex->GetDataPtr();
	WashColor(p,surf_width,surf_height,delT);
	tex->UnMap();
}

Quad::Quad()
{
	mesh	 = std::make_shared<QuadMesh>();
	renderer = std::make_shared<CudaRenderer>();
	renderer->BindBuffer(mesh);
	renderer->SetDrawMode(GL_TRIANGLES);
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
	mesh->Update(t);
}