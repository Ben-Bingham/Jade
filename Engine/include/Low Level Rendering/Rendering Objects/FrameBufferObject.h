#pragma once
#include <vector>

#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"
#include "Low Level Rendering/Rendering Objects/Texture.h"
#include "Low Level Rendering/Rendering Objects/Cubemap.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class FrameBufferObject {
	public:
		FrameBufferObject(Texture depthComponent) {
			glGenFramebuffers(1, &m_FBO);

			bind();

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthComponent.getTexture(), 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				LOG("Framebuffer failed to be created", ERROR);
				unbind();
			}
		}

		FrameBufferObject(Cubemap depthComponent) {
			glCheckError();
			glGenFramebuffers(1, &m_FBO);
			glCheckError();

			bind();
			glCheckError();

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthComponent.getCubemap(), 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glCheckError();

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				LOG("Framebuffer failed to be created", ERROR);
				unbind();
			}
			glCheckError();

		}

		void bind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		}

		static void unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void dispose() {
			glDeleteFramebuffers(1, &m_FBO);
		}

	private:
		unsigned int m_FBO;
	};
}