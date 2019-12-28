#pragma once
#include <GL/glew.h>
namespace bogong {
	class RenderBuffer {
	protected:
		GLuint id;
	public:
		RenderBuffer()
		{
			glGenRenderbuffers(1, &id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		}
		void Bind() {
			glBindRenderbuffer(GL_RENDERBUFFER, id);
		}
		GLuint GetID() {
			return id;
		}
	};
}