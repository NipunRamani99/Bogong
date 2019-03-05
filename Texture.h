#pragma once
#include <gl/glew.h>
class Texture
{
private:
	unsigned int m_TexID = 0;
public:
	Texture() = default;
	Texture(unsigned int p_Width, unsigned int p_Height, unsigned char * p_TextureBufferData)
	{
		glGenTextures(1, &m_TexID);
		glBindTexture(GL_TEXTURE, m_TexID);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p_Width, p_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_TextureBufferData);
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