#pragma once

#include <vector>

#include <GL/glew.h>

#include "Core Systems/Resource Pipeline/Image.h"
#include "Core Systems/Logging/OpenGLErrors.h"

namespace Jade {
	class Cubemap {
	public:
		// Images should be in the follwing order:
		/*
		right
		left
		top
		bottom
		front
		back
		*/
		Cubemap(std::vector<Image> images) : m_Images(images) {
			glGenTextures(1, &m_Cubemap);

			bind();
			int count = 0;
			for (Image& image : m_Images) {
				GLenum imageFormat;
				if (image.getChannels() == 3) {
					imageFormat = GL_RGB;
				}
				else if (image.getChannels() == 4) {
					imageFormat = GL_RGBA;
				}
				else {
					LOG("Unrecognized number of channels", Jade::WARNING);
					imageFormat = GL_RGB;
				}

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + count, 0, imageFormat, image.getWidth(), image.getHeight(), 0, imageFormat, GL_UNSIGNED_BYTE, &image.getContent()[0]);
				++count;
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		Cubemap(int imageWidths, int imageHeights, int imageFormat) : m_Images() {
			glCheckError();

			glGenTextures(1, &m_Cubemap);
			glCheckError();

			bind();
			for (int count = 0; count < 6; ++count) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + count, 0, imageFormat, imageWidths, imageHeights, 0, imageFormat, GL_FLOAT, NULL);
			}
			glCheckError();

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glCheckError();

		}

		void bind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, m_Cubemap); }

		static void unbind() { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

		void dispose() { glDeleteTextures(1, &m_Cubemap); }

		unsigned int getCubemap() const { return m_Cubemap; }

	private:
		unsigned int m_Cubemap;
		std::vector<Image> m_Images;
	};
}