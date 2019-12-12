#pragma once
#include <GL/glew.h>
namespace bogong {
	class FrameBuffer {
	protected:
		GLuint id;
	public:
		FrameBuffer()
		{
			glCreateFramebuffers(1,&id);
		}
		void Bind() {
			glBindBuffer(GL_FRAMEBUFFER, id);
		}
		void Draw() {
			glBindBuffer(GL_DRAW_FRAMEBUFFER, id);
		}
		void Read() {
			glBindBuffer(GL_READ_FRAMEBUFFER, id);
		}
		void Unbind() {
			glBindBuffer(GL_FRAMEBUFFER,0);
		}
	};
}