#pragma once
#include <memory>
#include "../Rendering/CudaRenderer.hpp"
#include "RunCuda.hpp"
namespace bogong {
	namespace cuda {
		class WaveMesh : public CudaMesh
		{
		private:
			int width = 100;
			float freq = 0.5f;
			std::vector<float3> vertices;
		public:
			VertexBuffer vbo;
			VertexBuffer vbo2;
			WaveMesh(int n, float freq)
				:
				width(n),
				freq(freq)
			{
				m_Color.resize(width*width);
				for (int i = 0; i < width*width; i++)
				{
					m_Color[i].x = 1.0f;
					m_Color[i].y = 0.0f;
					m_Color[i].z = 0.0f;
					m_Color[i].w = 1.0f;
				}
				count = width * width;
				CudaVBO<float3> * cvbo = new CudaVBO<float3>(width  * width * sizeof(float3));
				cvbo->Map();
				cvbo->GetMappedPointer();
				UpdateMesh_(cvbo->GetData(), width, width, 4);
				cvbo->UnMap();
				vbo2 = VertexBuffer(m_Color.data(), m_Color.size() * sizeof(float4));
				VertexBufferLayout layout1;
				layout1.AddElement<float>(3);
				VertexBufferLayout layout2;
				layout2.AddElement<float>(4);
				std::unique_ptr<VertexBuffer> ptr1{ cvbo };
				std::unique_ptr<VertexBuffer> ptr2 = std::make_unique<VertexBuffer>(vbo2);

				m_BufferVertex.push_back(std::make_pair(std::move(ptr1), layout1));
				m_BufferVertex.push_back(std::make_pair(std::move(ptr2), layout2));
			}
			WaveMesh & operator=(WaveMesh & wave)
			{
				m_BufferVertex = std::move(wave.m_BufferVertex);
				return *this;
			}
			WaveMesh()
			{

			}
			void Update() override
			{
				CudaVBO<float3>* t = (CudaVBO<float3>*)m_BufferVertex[0].first.get();
				t->Map();
				t->GetMappedPointer();
				UpdateMesh_(t->GetData(), width, width, 3);
				t->UnMap();
			}
		};
		class Wave
		{
		private:
			CudaRenderer renderer;
			int n;
		public:
			Wave()
			{
			}
			Wave(int n)
				:
				n(n)
			{
				renderer = std::move(CudaRenderer(WaveMesh(n, 0.5)));
				renderer.SetDrawMode(GL_POINTS);

			}
			Wave & operator=(Wave && wave)
			{
				renderer = std::move(wave.renderer);
				n = wave.n;
				return *this;
			}
			void Draw()
			{
				glPointSize(2.0f);
				renderer.RenderMesh();
			}
			void Test(float time)
			{
				auto &m_BufferVertex = renderer.GetBuffer();
				CudaVBO<float3>* t = (CudaVBO<float3>*)m_BufferVertex[0].first.get();
				t->Map();
				t->GetMappedPointer();
				UpdateMesh_(t->GetData(), n, n, time);
				t->UnMap();
			}
			void SetShader(Shader p_Shader)
			{
				renderer.SetShader(p_Shader);
				p_Shader.setBool("isTextured", false);
			}
		};
	}
}