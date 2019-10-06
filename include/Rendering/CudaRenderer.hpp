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
			{	
				m_VAO = VertexArray();
			}
		
			template<typename T>
			void RenderMesh(const std::shared_ptr<T> & cumesh)
			{
				m_VAO.Bind();
				m_Shader.Bind();
				if (cumesh->GetIndexBuffer().GetID() != 0)
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawElements(DrawMode, count, GL_UNSIGNED_INT, 0); };
				}
				else
				{
					m_DrawCall = [](GLenum DrawMode, int count) { glDrawArrays(DrawMode, 0, count);  };
				}
			
				int count = cumesh->GetCount();
				m_Shader.setMat4("model",m_Model);
				m_DrawCall(m_DrawMode, count);
				error();
			}
			template<typename T>
			void BindBuffer(const std::shared_ptr<T> & cumesh)
			{
				m_VAO.Bind();
				m_Shader.Bind();
				cumesh->Bind();
				error();
			}
			template<typename T>
			void UnbindBuffer(const std::shared_ptr<T> & cumesh)
			{
				cumesh->Unbind();
				m_VAO.Unbind();	
			}
		};
	}
}