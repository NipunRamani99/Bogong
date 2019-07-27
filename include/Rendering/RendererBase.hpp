#pragma once
#include "../VertexArray.hpp"
#include "../Shaders.hpp"
#include "../VertexBufferLayout.hpp"
#include "Mesh.hpp"
#include "../Globals.h"
#include <string>
#include <functional>
#include <map>
namespace bogong
{
	class RendererBase
	{
	protected:
		GLenum m_DrawMode;
		Shader m_Shader;
		using DrawCall = std::function<void(GLenum, int)>;
		DrawCall  m_DrawCall = [](GLenum, int)-> void {};
	public:
		virtual void BindBuffer()=0;
		virtual void UnbindBuffer()=0;
		virtual void RenderMesh()=0;
		RendererBase() {}
		RendererBase & operator=(RendererBase && rb)
		{
			m_DrawCall = std::move(rb.m_DrawCall);
			m_Shader = std::move(rb.m_Shader);
			m_DrawMode = std::move(rb.m_DrawMode);
			return *this;
		}
		RendererBase(RendererBase && rb)
		{
			m_DrawCall = std::move(rb.m_DrawCall);
			m_DrawMode = std::move(rb.m_DrawMode);
			m_Shader = std::move(rb.m_Shader);
		}
		void SetShader(Shader p_Shader)
		{
			m_Shader = p_Shader;
		}
		void SetDrawMode(GLenum p_DrawMode)
		{
			m_DrawMode = p_DrawMode;
		}
		void SetDrawCall(DrawCall p_DrawCall)
		{
			m_DrawCall = p_DrawCall;
		}

	};
}