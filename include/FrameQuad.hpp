#pragma once
#include "Shaders.hpp"
#include "Vertex.h"
#include "Globals.h"
#include "Texture.h"
#include <memory>
#include <assert.h>
#include "Rendering/CudaRenderer.hpp"
#include "Rendering/CudaMesh.hpp"
namespace bogong {
	class FrameBufferQuadMesh : public cuda::CudaMesh
	{
	private:
		std::shared_ptr<VertexBuffer> vbo;
	public:
		FrameBufferQuadMesh() {
			count = 6;
			float vertices[] = {
					 -1.0f,-1.0f,0.0f, 0.0f,0.0f,
					 -1.0f,1.0f,0.0f,  0.0f,1.0f,
					  1.0f,1.0f,0.0f,  1.0f,1.0f,

					 1.0f,-1.0f,0.0f, 1.0f,0.0f,
					 1.0f,1.0f,0.0f,  1.0f,1.0f,
					-1.0f,-1.0f,0.0f, 0.0f,0.0f
			};
			vbo = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
			VertexBufferLayout vbl;
			vbl.AddElement<float>(3);
			vbl.AddElement<float>(2);
			auto buffer1 = std::make_pair(vbo, vbl);
			m_BufferVertex.push_back(buffer1);

		}
		void AddTexture(const std::shared_ptr<Texture> & tex) {
			m_TexVector.push_back(tex);
		}
	};
	class FrameBufferQuad {
	private:
		std::shared_ptr<FrameBufferQuadMesh> mesh;
		std::shared_ptr<cuda::CudaRenderer> renderer;
	public:
		FrameBufferQuad() {
			mesh     = std::make_shared<FrameBufferQuadMesh>();
			renderer = std::make_shared<cuda::CudaRenderer>();
			renderer->SetDrawMode(GL_TRIANGLES);
			renderer->BindBuffer(mesh);
		}
		void AddTexture(const std::shared_ptr<Texture> & tex)  {
			mesh->AddTexture(tex);
			renderer->BindBuffer(mesh);
		}
		void SetShader(Shader & shader) {
			renderer->SetShader(shader);
			assert(!error());
		}
		void Draw() {
			renderer->RenderMesh(mesh);
			assert(!error());
		}

	};
}