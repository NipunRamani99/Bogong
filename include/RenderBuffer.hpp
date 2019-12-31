#pragma once
#include <GL/glew.h>
namespace bogong {
	class RenderBuffer {
	protected:
		GLuint id;
		unsigned int width = 0;
		unsigned int height = 0;
	public:
		RenderBuffer()
		{
			glGenRenderbuffers(1, &id);
		}
		void Bind(){
			glBindRenderbuffer(GL_RENDERBUFFER, id);
		}
		void BufferStorage(unsigned int _width, unsigned int _height) {
			width = _width;
			height = _height;
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		}
		GLuint GetID() {
			return id;
		}
		void Unbind() {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	};
}