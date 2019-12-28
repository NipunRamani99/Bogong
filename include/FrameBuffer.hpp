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
		void AttachTexture(GLuint texture) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		}
		void AttachRenderBuffer(GLuint rbo) {
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		}
		bool isComplete() {
			return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		}
		void Unbind() {
			glBindBuffer(GL_FRAMEBUFFER,0);
		}
	};
}