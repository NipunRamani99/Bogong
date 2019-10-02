#pragma once
#include "Rendering/CudaRenderer.hpp"
#include "Rendering/Renderer.hpp"
#include "RunKernel.h"
#include<ctime>
namespace bogong {
	namespace cuda {
		class WaveMesh : public CudaMesh
		{
		private:
			int width =100;
			float freq = 0.5f;
			
		public:
			VertexBuffer vbo;
			VertexBuffer vbo2;
			WaveMesh(int n,float freq)
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
				CudaVBO<float3> * cvbo = new CudaVBO<float3>( width  * width * sizeof(float3));
				cvbo->Map();
				cvbo->GetMappedPointer();
				UpdateMesh(cvbo->GetData(), width, width, 4);
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
			void Update() override {}
			void Update2(float time) 
			{
				CudaVBO<float3>* t = (CudaVBO<float3>*)m_BufferVertex[0].first.get();
				t->Map();
				t->GetMappedPointer();
				UpdateMesh(t->GetData(), width,width,time);
				t->UnMap();
			}
		};
		class Wave
		{
		private:
			std::shared_ptr<CudaRenderer> renderer;
			std::shared_ptr<WaveMesh> wave;
			int n;
		public:
			Wave()
			{
			}
			Wave(int n)
				:
				n(n)
			{
				wave = std::make_shared<WaveMesh>(100, 0.4);
				renderer = std::make_shared<CudaRenderer>();
				renderer->BindBuffer(wave);
				renderer->SetDrawMode(GL_POINTS);
			}
			/*Wave & operator=(Wave && wave)
			{
				renderer = std::move(wave.renderer);
				n = wave.n;
				return *this;
			}*/
			void Draw()
			{
				glPointSize(2.0f);
				renderer->RenderMesh(wave);
			}
			void Update(float t)
			{
				wave->Update2(t);
			}
			void SetShader(Shader p_Shader)
			{
				renderer->SetShader(p_Shader);
				p_Shader.setBool("isTextured", false);
			}
		};
	}
}