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
			std::shared_ptr<CudaVBO<float4>> colors;
			std::shared_ptr<CudaVBO<float3>> cvbo;
		public:
			WaveMesh(int n,float freq)
				:
				width(n),
				freq(freq)
			{
				
				count = width * width;
				cvbo = std::make_shared<CudaVBO<float3>>( width  * width * sizeof(float3),GL_DYNAMIC_DRAW);
				cvbo->Map();
				cvbo->GetMappedPointer();
				UpdateMesh(cvbo->GetData(), width, width, 4);
				cvbo->UnMap();
                colors = std::make_shared<CudaVBO<float4>>(width*width*sizeof(float4));
				VertexBufferLayout layout1;
				layout1.AddElement<float>(3);
				VertexBufferLayout layout2;
				layout2.AddElement<float>(4);
				
			    m_BufferVertex.push_back(std::make_pair(cvbo, layout1));
				m_BufferVertex.push_back(std::make_pair(colors, layout2));
			}
			WaveMesh & operator=(WaveMesh & wave)
			{
				m_BufferVertex = std::move(wave.m_BufferVertex);
				return *this;
			}
			WaveMesh()
			{	
			}
			
			void Update2(float time) 
			{
				cvbo->Map();
				cvbo->GetMappedPointer();
				UpdateMesh(cvbo->GetData(), width,width,time);
				cvbo->UnMap();
				
				colors->Map();
				colors->GetMappedPointer();
				UpdateColors(colors->GetData(), width, width, time);
				colors->UnMap();
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
				wave = std::make_shared<WaveMesh>(n, 0.4f);
				renderer = std::make_shared<CudaRenderer>();
				renderer->BindBuffer(wave);
				renderer->SetDrawMode(GL_POINTS);
			}
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