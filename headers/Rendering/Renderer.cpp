#pragma once

#include "Renderer.hpp"
namespace bogong {
	void Renderer::RenderMesh()
	{
		BindBuffer();

		UnbindBuffer();
	}
	void Renderer::BindBuffer()
	{
		m_VAO.Bind();
		error();
		m_Mesh.GetVertexBuffer().Bind();
		m_Mesh.GetIndexBuffer().Bind();
		m_Shader.Bind();
		int stride = m_Layout.GetStride();
		int offset = 0;
		int i = 0;
		for (auto element : m_Layout.GetElements())
		{
			glEnableVertexAttribArray(i);
			i++;
		}
		error();
		i = 0;
		for (auto element : m_Layout.GetElements())
		{
			glVertexAttribPointer(i, element.count, element.type, element.isNormalized, sizeof(Vertex<float>), (void*)(offset));
			offset += element.count * sizeof(element.type);
			i++;
		}
		m_Shader.setMat4("model", m_Model);
		error();
		int count = m_Mesh.GetCount();
		m_DrawCall(m_DrawMode, count);
		error();
	}
	void Renderer::UnbindBuffer()
	{
		m_Mesh.GetIndexBuffer().Unbind();
		m_Mesh.GetVertexBuffer().Unbind();
		m_VAO.Unbind();
	}
}