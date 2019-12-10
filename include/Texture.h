#pragma once
#include <gl/glew.h>
namespace bogong {
	class Texture
	{
	protected:
		unsigned int m_TexID = 0;
		size_t size = 0;
	public:
		Texture() = default;
		Texture(size_t p_size, unsigned int p_width, unsigned int p_height, void * p_texturebufferdata, GLuint format) {
			size = p_size;
			glGenTextures(1, &m_TexID);
			glBindTexture(GL_TEXTURE, m_TexID);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, format, p_width, p_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_texturebufferdata);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE, 0);
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
		void Bind()
		{
			glBindTexture(GL_TEXTURE, m_TexID);
		}
		void Unbind()
		{
			glBindTexture(GL_TEXTURE, 0);
		}
	};
}