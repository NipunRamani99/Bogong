#include "../Rendering/CudaMesh.hpp"
#include "../Rendering/CudaRenderer.hpp"
#include "../Vertex.h"
namespace bogong {
	namespace cuda {
		namespace viz {
			class OriginVizMesh : public CudaMesh
			{
			private:
				std::shared_ptr<VertexBuffer> vert_buff;
			public:
				OriginVizMesh() {		//Vertex Pos     //Colour
					float vertices[] = {0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,1.0f,
										1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,1.0f,
										0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,1.0f,
										0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f,1.0f,
										0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
										0.0f,0.0f,1.0f, 0.0f,0.0f,1.0f,1.0f };
					vert_buff = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
					VertexBufferLayout vbl;
					vbl.AddElement<float>(3);
					vbl.AddElement<float>(4);
					auto buff1 = std::make_pair(vert_buff, vbl);
					m_BufferVertex.push_back(buff1);
					count = 6;
				}
			};
			class OriginViz {
			private:
				std::shared_ptr<OriginVizMesh> mesh;
				std::shared_ptr<CudaRenderer> renderer;
			public:
				OriginViz() {
					mesh = std::make_shared<OriginVizMesh>();
					renderer = std::make_shared<CudaRenderer>();
					renderer->SetDrawMode(GL_LINES);
					renderer->BindBuffer(mesh);
				}
				void SetShader(Shader & shader) {
					renderer->SetShader(shader);
				}
				void Draw() {
					renderer->RenderMesh(mesh);
				}
			};
		}
	}
}