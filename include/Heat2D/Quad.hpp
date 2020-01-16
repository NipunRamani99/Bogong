#pragma once
#include "../Rendering/CudaRenderer.hpp"
#include "../CudaVBO.h"
#include "../VertexBuffer.hpp"
#include "../CudaTexture.hpp"
#include "../Shaders.hpp"
#include "CudaBuffer.hpp"
namespace bogong {
	namespace cuda {
		
		namespace Heat2D {
			class QuadMesh : public CudaMesh
			{
			private:
				std::shared_ptr<VertexBuffer> vbo;
				std::shared_ptr<cuda::CudaTexture> tex;
				int surf_width  = 512;
				int surf_height = 512;
				CudaBuffer<float> grid;
			public:
				QuadMesh();
				void ProcessInput();
				void Update(float delT);
			};
			class Quad {
				std::shared_ptr<QuadMesh> mesh;
				std::shared_ptr<CudaRenderer> renderer;
			public:
				Quad();
				void SetShader(Shader shader);
				void Draw();
				void Update(float delT);
			};
		}
	}
}