#include "Rendering/CudaRenderer.hpp"
#include "CudaVBO.h"
#include "RunKernel.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory>
#include "IndexBuffer.h"
namespace bogong {

	namespace cuda {
		class GerstnerWaveMesh : public CudaMesh
		{
		private:
			std::shared_ptr<CudaVBO<float3>> vertex_cvbo;
			std::shared_ptr<CudaVBO<float4>> color_cvbo;
			std::shared_ptr<CudaVBO<float3>> normals_cvbo;
			MeshProp meshprop;
			int rows = 0;
			float width = 0.0f;
			int n = 4;
			std::vector<float3> vertices;
			std::vector<float4> colors;
			std::vector<unsigned int> indices;
			VertexBufferLayout layout1;
			VertexBufferLayout layout2;
			VertexBufferLayout layout3;
			float amplitude = 0.5f;
			 float counter = 0.0f;
		public:
			WaveProp props[4];

			GerstnerWaveMesh(int rows, float width);

			void Update();

			void ReadInputs();

			void Update(float time);

			void Amplitude(float amplitude);

		private:
			inline void makeLayout();

			void makeVBO();

			void makeIBO();

			void makeIndicesQuads();

			void makeIndicesLines();

			void makeMesh();

			float3 makeVertex(int x, int z, float delX, float delZ);

			float4 makeColor();
		};
		class GerstnerWave
		{
		private:
			std::shared_ptr<CudaRenderer> linerenderer;
			std::shared_ptr<CudaRenderer> pointrenderer;
			std::shared_ptr<GerstnerWaveMesh> grid_mesh;
			inline void initMesh(int n, float width)
			{
				grid_mesh = std::make_shared<GerstnerWaveMesh>(n,width);
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
			GerstnerWave(int n,float width)
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
			void Input()
			{
				grid_mesh->ReadInputs();
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
