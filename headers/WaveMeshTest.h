#pragma once
#include "Rendering/CudaRenderer.hpp"

namespace bogong {
	namespace cuda {
		
		class WaveMesh : public CudaMesh
		{
		private:
			int width =100;
			float freq = 0.5f;

		public:
			WaveMesh(int n,float freq)
				:
				width(n),
				freq(freq)
			{
				m_VertPos.resize(width*width);
				m_Color.resize(width*width);
				for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < width; y++)
					{
						m_VertPos[x + y * width].x = float(x) / float(width);
						m_VertPos[x + y * width].y = 0.0f;
						m_VertPos[x + y * width].z = float(y) / float(width);
						m_Color[x + y * width].x = 1.0f;
						m_Color[x + y * width].w = 1.0f;
					}
				}
				CudaVBO<float3> vbo = CudaVBO<float3>(m_VertPos.data(),m_VertPos.size()*sizeof(float3));
				VertexBuffer vbo2 = VertexBuffer(m_Color.data(), m_Color.size() * sizeof(float4));
				VertexBufferLayout layout1;
				layout1.AddElement<float>(3);
				VertexBufferLayout layout2;
				layout2.AddElement<float>(4);
				auto ptr1 = std::make_shared<VertexBuffer>(vbo);
				auto ptr2 = std::make_shared<VertexBuffer>(vbo2);
				m_BufferVertex.push_back(std::make_pair(ptr1, layout1));
				m_BufferVertex.push_back(std::make_pair(ptr2, layout2));
			}
			WaveMesh()
			{
				
			}
			
		};
		class Wave
		{
		private:
			WaveMesh mesh;
			CudaRenderer renderer;
		public:
			Wave()
			{
			}
			Wave(int n)
			{
				mesh = std::move(WaveMesh(n, 0.5));
				renderer = std::move(CudaRenderer(mesh));
				renderer.SetDrawMode(GL_POINTS);
			}
			Wave(Wave && wave)
			{
				mesh = std::move(wave.mesh);
				renderer = std::move(wave.renderer);
			}
			Wave & operator=(Wave && wave)
			{
				mesh = std::move(wave.mesh);
				renderer = std::move(wave.renderer);
				return *this;
			}
			void Draw()
			{
				renderer.RenderMesh();
			}
			void SetShader(Shader p_Shader)
			{
				renderer.SetShader(p_Shader);
			}
		};
	}
}