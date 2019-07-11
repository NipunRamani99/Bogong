#pragma once 

#include "../VertexArray.hpp"
#include "../Shaders.hpp"
#include "../VertexBufferLayout.hpp"
#include "RendererBase.hpp"
#include "CudaMesh.hpp"
#include "../Globals.h"
#include <functional>
#include <memory>
namespace bogong {
	namespace cuda {
		class CudaRenderer :public RendererBase
		{
		private:
			CudaMesh m_cuMesh;
			VertexArray m_VAO;
			glm::mat4 m_Model = glm::mat4(1.0);

		public:
			CudaRenderer() = default;

			CudaRenderer(CudaMesh & p_Mesh)
				:
				m_cuMesh(p_Mesh)
			{
				m_cuMesh = p_Mesh;
				if (m_cuMesh.GetIndexBuffer().GetID() != 0)
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawElements(DrawMode, count, GL_UNSIGNED_INT, 0); };
				}
				else
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawArrays(DrawMode, 0, count);  };
				}
				m_VAO = VertexArray();
			}
			CudaRenderer & operator=(CudaRenderer && p_Renderer)
			{
				m_cuMesh = std::move(p_Renderer.m_cuMesh);
				m_DrawCall = std::move(p_Renderer.m_DrawCall);
				m_Model = std::move(p_Renderer.m_Model);
				m_VAO = std::move(p_Renderer.m_VAO);
				m_DrawMode = std::move(p_Renderer.m_DrawMode);
				m_Shader = std::move(p_Renderer.m_Shader);
				return *this;
			}
			CudaRenderer(CudaRenderer && renderer)
				:
				m_cuMesh(std::move(renderer.m_cuMesh)),
				m_VAO(std::move(renderer.m_VAO))
			{

			}
			
			void RenderMesh()
			{
				BindBuffer();
				
				int count = m_cuMesh.GetCount();
				m_DrawCall(m_DrawMode, count);
				error();
				UnbindBuffer();
			}
			void BindBuffer()
			{
				m_VAO.Bind();
				m_Shader.Bind();
				auto buffvertex = m_cuMesh.GetBufferVertex();
				int i = 0;
				error();
				for (auto & pair : buffvertex)
				{
					for (auto & elem : pair.second.GetElements())
					{
						glEnableVertexAttribArray(i);
						i++;
					}
				}
				i = 0;
				error();
				for (auto & pair : buffvertex)
				{
					auto buffer = *pair.first;
					buffer.Bind();
					int offset = 0;
					for (auto & elem : pair.second.GetElements())
					{

						glVertexAttribPointer(i, elem.count, elem.type, elem.isNormalized, buffer.GetStride(), (void*)offset);
						offset += elem.count * sizeof(elem.type);
					}
				}
				error();
			}
			void UnbindBuffer()
			{
				for(auto & vp : m_cuMesh.GetBufferVertex())
				{
					auto buffer = *vp.first;
					buffer.Unbind();
				}
				m_cuMesh.GetIndexBuffer().Unbind();
			    m_VAO.Unbind();
			}
		};
	}
}