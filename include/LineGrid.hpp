#include "Rendering/CudaRenderer.hpp"
#include "CudaVBO.h"
#include "RunKernel.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory>
#include "IndexBuffer.h"
namespace bogong {

	namespace cuda {
		class LineGridMesh : public CudaMesh
		{
		private:
			std::shared_ptr<CudaVBO<float3>> vertex_cvbo;
			std::shared_ptr<CudaVBO<float4>> color_cvbo;
			
			int rows = 0;
			float width = 0.0f;
			std::vector<float3> vertices;
			std::vector<float4> colors;
			std::vector<unsigned int> indices;
			VertexBufferLayout layout1;
			VertexBufferLayout layout2;
			float amplitude = 0.5f;
		public:
			WaveProp props[4];
			
			LineGridMesh(int rows,float width)
				:
				rows(rows),
				width(width)
			{
				makeMesh();
				makeVBO();
				makeLayout();
				makeIndicesLines();
				makeIBO();
				m_BufferVertex.push_back(std::make_pair(std::dynamic_pointer_cast<VertexBuffer>(vertex_cvbo), layout1));
				m_BufferVertex.push_back(std::make_pair(std::dynamic_pointer_cast<VertexBuffer>(color_cvbo), layout2));	
				props[0].amplitude = 0.001;
				props[1].amplitude = 0.004;
				props[2].amplitude = 0.004;
				props[3].amplitude = 0.002;
				props[0].isCircular = 0;
				props[1].isCircular = 0xFF;
				props[2].isCircular = 0xFF;
				props[3].isCircular = 0;
				props[0].dirx = 1.0f / sqrt(2);
				props[0].diry = 1.0f / sqrt(2);
				
				props[1].x = 0.5f;
				props[1].y = 0.1f;
				
				props[2].x = 0.1f;
				props[2].y = 0.3f;

				props[3].dirx = 0.0f;
				props[3].diry = 1.0f;

				props[0].w = props[1].w = props[2].w = props[3].w = 1.0f;
				
				
			}
			void Update()
			{

			}
			void Update(float time)
			{
				vertex_cvbo->Map();
				vertex_cvbo->GetMappedPointer();
				GerstnerTest(vertex_cvbo->GetData(), rows, rows,amplitude ,time);
				vertex_cvbo->UnMap();
				color_cvbo->Map();
				color_cvbo->GetMappedPointer();
				UpdateColors(color_cvbo->GetData(), rows, rows, 2.5f*time);
				color_cvbo->UnMap();
				
			}
			void Amplitude(float amplitude)
			{
				this->amplitude = amplitude;
			}
		private:
			inline void makeLayout()
			{
				layout1.AddElement<float>(3);
				layout2.AddElement<float>(4);
			}
			void makeVBO()
			{
				vertex_cvbo = std::make_shared<CudaVBO<float3>>(vertices);
				color_cvbo	= std::make_shared<CudaVBO<float4>>(colors);
			}
			void makeIBO()
			{
				m_IBO = bogong::IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));
			}
			void makeIndicesQuads()
			{
				unsigned int idx = 0;

				for (int j = 0; j < rows - 1; j++)
				{
					for (int i = 0; i < rows - 1; i++) {
						indices.push_back(idx);
						indices.push_back(idx +rows);
						indices.push_back(idx + rows + 1);
						indices.push_back(idx + 1);
						idx++;
					}
					idx++;
				}
				count = indices.size();
			}
			void makeIndicesLines()
			{
				unsigned int idx = 0;
				
				for (int j = 0; j < rows-1; j++)
				{
					for (int i = 0; i < rows-1; i++) {
						indices.push_back(idx);
						indices.push_back(idx+1);
						indices.push_back(idx);
						indices.push_back(idx +rows);
						indices.push_back(idx + 1);
						indices.push_back(idx + rows+1);
						indices.push_back(idx + rows);
						indices.push_back(idx + rows + 1 );
						idx++;
					}
					idx++;
				}
				count = indices.size();
			}
			void makeMesh()
			{
				vertices.resize(rows*rows);
				colors.resize(rows*rows);
				float delX = width / (float)rows;
				float delZ = delX;
				unsigned int idx = 0;
				for (int x = 0; x < rows; x++)
				{
					for (int z = 0; z < rows; z++)
					{
						vertices[idx] = makeVertex(x, z,delX, delZ);
						colors[idx] = makeColor();
						idx++;
					}
				}
				count = rows*rows;
			}
			float3 makeVertex(int x, int z,float delX, float delZ)
			{
				float3 vertex;
				vertex.x = float(x)*delX - width/2.0f;
				vertex.z = float(z)*delZ - width/2.0f;
				float freq = 1.5f;
				vertex.y = 0.0f;//sin(vertex.x*freq) + cos(vertex.z*freq);
				return vertex;
			}
			float4 makeColor()
			{
				float4 color;
				color.x = 1.0f;
				color.y = 0.0f;
				color.z = 0.0f;
				color.w = 1.0f;
				return color;
			}
			
		};
		class LineGrid
		{
		private:
			std::shared_ptr<CudaRenderer> linerenderer;
			std::shared_ptr<CudaRenderer> pointrenderer;
			std::shared_ptr<LineGridMesh> grid_mesh;
			inline void initMesh(int n, float width)
			{
				grid_mesh = std::make_shared<LineGridMesh>(n,width);
			}
			inline void initRenderer()
			{
				linerenderer = std::make_shared<CudaRenderer>();
				linerenderer->SetDrawMode(GL_LINES);
				linerenderer->BindBuffer(grid_mesh);
				pointrenderer = std::make_shared<CudaRenderer>();
				pointrenderer->SetDrawMode(GL_POINTS);
				pointrenderer->BindBuffer(grid_mesh);
			}
		public:
			LineGrid(int n,float width)
			{
				initMesh(n, width);
				initRenderer();
			}
			void SetShader(Shader & shader)
			{
				linerenderer->SetShader(shader);
				pointrenderer->SetShader(shader);
			}
			void Update(float t)
			{
				grid_mesh->Update(t);
			}
			void SetAmplitude(float amplitude)
			{
				grid_mesh->Amplitude(amplitude);
			}
			void Draw()
			{
				linerenderer->RenderMesh(grid_mesh);
				//glPointSize(4.0f);
				//pointrenderer->RenderMesh(grid_mesh);
			}
		};
	}
}
