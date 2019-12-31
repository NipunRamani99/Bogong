#pragma once
#include <gl/glew.h>
#include <gl/GL.h>
#include "Globals.h"
#include<vector>
namespace bogong {
	class Texture
	{
	protected:
		unsigned int m_TexID = 0;
		size_t size = 0;
		GLuint target {GL_TEXTURE_2D};
	public:
		Texture() = default;
		template<typename T>
		Texture(std::vector<T>& surface,size_t width, size_t height ,GLuint format, GLuint data_type,GLuint texture_target)
		{
			size = surface.size();
			glGenTextures(1, &m_TexID);
			glBindTexture(texture_target, m_TexID);
			target = texture_target;
			assert(!error());
			glTextureParameteri(m_TexID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_TexID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(m_TexID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTextureParameteri(m_TexID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTextureParameteri(m_TexID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			assert(!error());
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, data_type, surface.data());
			assert(!error());

			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			assert(!error());

		}
		Texture(size_t p_size, unsigned int p_width, unsigned int p_height, void * p_texturebufferdata, GLuint format,GLuint channels,GLuint texture_target,GLuint datatype) {
			size = p_size;
			glGenTextures(1, &m_TexID);
			assert(!error());
			glBindTexture(texture_target, m_TexID);
			target = texture_target;
			assert(!error());
			glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			assert(!error());
			glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, format, p_width, p_height, 0, channels, datatype, p_texturebufferdata);
			assert(!error());
			glBindTexture(GL_TEXTURE_2D, 0);
			assert(!error());

		}
		Texture(size_t p_size,unsigned int p_width, unsigned int p_height, unsigned char * p_texturebufferdata)
		{
			size = p_size;
			glGenTextures(1, &m_TexID);
			glBindTexture(GL_TEXTURE, m_TexID);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_width, p_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_texturebufferdata);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE, 0);
		}
		unsigned int GetID()
		{
			return m_TexID;
		}
		void Bind()
		{
			glBindTexture(target, m_TexID);
			assert(!error());
		}
		void Unbind()
		{
			glBindTexture(GL_TEXTURE, 0);
		}
	};
}