#pragma once
#include "../Rendering/CudaRenderer.hpp"
#include "../CudaVBO.h"
#include "../VertexBuffer.hpp"
#include "../CudaTexture.hpp"
#include "../Shaders.hpp"

namespace bogong {
	namespace cuda {
		namespace StableFluid {
			class QuadMesh : public CudaMesh
			{
			private:
				std::shared_ptr<VertexBuffer> vbo;
				std::shared_ptr<CudaTexture> tex;
				int surf_width = 0;
				int surf_height = 0;
			public:
				QuadMesh();
				void ProcessInput();
				void Update();
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