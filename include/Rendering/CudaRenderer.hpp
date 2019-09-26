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
			
			VertexArray m_VAO;
			glm::mat4 m_Model = glm::mat4(1.0);

		public:
			CudaRenderer() 
			{};
			CudaRenderer()
			{	
				m_VAO = VertexArray();
			}
			/*CudaRenderer & operator=(CudaRenderer && p_Renderer)
			{
				m_cuMesh = std::move(p_Renderer.m_cuMesh);
				m_VAO = std::move(p_Renderer.m_VAO);
				m_Shader = std::move(p_Renderer.m_Shader);
				m_DrawCall = std::move(p_Renderer.m_DrawCall);
				m_DrawMode = std::move(p_Renderer.m_DrawMode);
				return *this;
			}*/
			void RenderMesh(const std::shared_ptr<CudaMesh> & cumesh)
			{
				if (cumesh->GetIndexBuffer().GetID() != 0)
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawElements(DrawMode, count, GL_UNSIGNED_INT, 0); };
				}
				else
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawArrays(DrawMode, 0, count);  };
				}
				BindBuffer(cumesh);
				int count = cumesh->GetCount();
				m_Shader.setMat4("model",m_Model);
				glDrawArrays(GL_POINTS, 0, count);
				error();
				UnbindBuffer(cumesh);
			}
			void BindBuffer(const std::shared_ptr<CudaMesh> & cumesh)
			{
				m_VAO.Bind();
				m_Shader.Bind();
				cumesh->Bind();
				error();
			}
			void UnbindBuffer(const std::shared_ptr<CudaMesh> & cumesh)
			{
				cumesh->Unbind();
				m_VAO.Unbind();
			}
			void Update(const std::shared_ptr<CudaMesh> & cumesh)
			{
				cumesh->Update();
			}
			std::vector<Buffer> & GetBuffer(const std::shared_ptr<CudaMesh> & cumesh)
			{
				return cumesh->GetBufferVertex();
			}
		};
	}
}