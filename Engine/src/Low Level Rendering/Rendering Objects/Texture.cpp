#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Image.h"
#include "Low Level Rendering/Rendering Objects/Texture.h"

namespace Jade {
	Texture::Texture(const Jade::Image& image) : m_Image(image) {
		glGenTextures(1, &m_Texture);

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum imageFormat;
		if (m_Image.getChannels() == 3) {
			imageFormat = GL_RGB;
		}
		else if (m_Image.getChannels() == 4) {
			imageFormat = GL_RGBA;
		}
		else {
			LOG("Unrecognized number of channels", Jade::WARNING);
			imageFormat = GL_RGB;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, m_Image.getWidth(), m_Image.getHeight(), 0, imageFormat, GL_UNSIGNED_BYTE, &m_Image.getContent()[0]);
		
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}