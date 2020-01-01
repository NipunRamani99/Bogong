#include "../Rendering/CudaMesh.hpp"
#include "../Rendering/CudaRenderer.hpp"
#include "../Defs.h"
namespace bogong {
	namespace cuda {
		namespace viz {
			struct point {
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				float r = 0.0f;
				float g = 0.0f;
				float b = 0.0f;
				float a = 0.0f;
			};
			class HeatmapMesh :public CudaMesh {
			private:
				std::shared_ptr<VertexBuffer> vert_buff ;
				float sigma = 0.3;
				float sigma2 = sigma * sigma;
			public:
				HeatmapMesh() {
					float max_val = -999.9f;
					float min_val = 999.9f;
					int grid_x = 400;
					int grid_y = 400;
					float sigma_const = 10.0f*(sigma2*2.0f*3.141592653f);
					const int num_points = grid_x * grid_y;
					size_t idx = 0;
					std::vector<point> vertices;
					vertices.resize(num_points);
					for (float x = -grid_x / 2.0f; x < grid_x / 2.0f; x += 1.0f) {
						for (float y = -grid_y / 2.0f; y < grid_x / 2.0f; y += 1.0f) {
							float x_data = 2.0f*x / grid_x;
							float y_data = 2.0f*y / grid_y;
							//set the mean to 0
							float z_data = exp(-0.5f*(x_data*x_data) / (sigma2)-0.5f*(y_data*y_data) / (sigma2)) / sigma_const;
							if (z_data > max_val)
								max_val = z_data;
							if (z_data < min_val)
								min_val = z_data;
							vertices[idx].x = x_data;
							vertices[idx].z = y_data;
							vertices[idx].y = z_data;
							idx++;
						}
					}
					float halfmax = (max_val + min_val) / 2.0f;
					for (size_t i = 0; i < idx; i++) {
					  float val = vertices[i].y;
					  float b = 1.0f - val / halfmax;
					  float r = val / halfmax - 1.0f;
					  if (b < 0.0f)
						  b = 0.0f;
					  if (r < 0.0f)
						  r = 0.0f;
					  float g = 1.0f - b - r;
					  if (g < 0.0f)
						  g = 0.0f;
					  vertices[i].r = r;
					  vertices[i].g = g;
					  vertices[i].b = b;
					  vertices[i].a = 0.250f;
					}
					vert_buff = std::make_shared<VertexBuffer>(vertices.data(), vertices.size()*sizeof(point));
					count = num_points;
					VertexBufferLayout vbl;
					vbl.AddElement<float>(3);
					vbl.AddElement<float>(4);
					auto buff = std::make_pair(vert_buff,vbl);
					m_BufferVertex.push_back(buff);
					
				}
			};
			class Heatmap {
			private:
				std::shared_ptr<HeatmapMesh> mesh;
				std::shared_ptr<CudaRenderer> renderer;
			public:
				Heatmap() {
					mesh = std::make_shared<HeatmapMesh>();
					renderer = std::make_shared<CudaRenderer>();
					renderer->BindBuffer(mesh);
					renderer->SetDrawMode(GL_POINTS);
				}
				void SetShader(Shader & shader) {
					renderer->SetShader(shader);
				}
				void Draw() {
					glPointSize(POINT_SIZE);
					renderer->RenderMesh(mesh);
				}
			};
		}
	}
}