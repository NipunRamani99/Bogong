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
			assert(!error());
		}
		void Bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, id);
			assert(!error());
		}
		void Draw() {
		}
		void Read() {
			glBindBuffer(GL_READ_FRAMEBUFFER, id);
		}
		
		void AttachTexture(GLuint texture,GLuint attachment) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);

		}
		void AttachRenderbuffer(GLuint rbo, GLuint attachment) {
			glFramebufferRenderbuffer(GL_FRAMEBUFFER,attachment, GL_RENDERBUFFER, rbo);
		}
		bool isComplete() {
			return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		}
		void Unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER,0);
		}
	};
}