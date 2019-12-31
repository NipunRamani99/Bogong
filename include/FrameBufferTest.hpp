#pragma once
#include<GL/glew.h>
#include "FrameBuffer.hpp"
#include "RenderBuffer.hpp"
#include "Texture.h"
#include "Globals.h"
#include <memory>
#include<assert.h>
namespace bogong {
	class FrameBufferTest {
	private:

		unsigned int width = 2732;
		unsigned int height = 1536;
		FrameBuffer fbo;
		std::shared_ptr<RenderBuffer> rbo;
		std::shared_ptr<Texture> colour_tex;
		
	public:
		FrameBufferTest() {
			assert(!error());
			size_t size = 0;
			colour_tex = std::make_shared<Texture>(size, width, height, nullptr, GL_RGB, GL_RGB, GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
			assert(!error());
			rbo = std::make_shared<RenderBuffer>();
			rbo->Bind();
			rbo->BufferStorage(width,height);
			assert(!error());
			fbo.Bind();
			assert(!error());
			fbo.AttachTexture(colour_tex->GetID(), GL_COLOR_ATTACHMENT0);
			assert(!error());
			fbo.AttachRenderbuffer(rbo->GetID(), GL_DEPTH_STENCIL_ATTACHMENT);
			assert(!error());
			while (!fbo.isComplete()) {

			}
			std::cout << "FBO is Ready\n";
			UnbindFBO();
			rbo->Unbind();
		}
		void BindFBO() {
			fbo.Bind();
		}
		void UnbindFBO() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		std::shared_ptr<Texture> & get_texture() {
			return colour_tex;
		}
		void BindTexBuff() {
			colour_tex->Bind();
		}
	};
}