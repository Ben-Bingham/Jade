#pragma once

#include <GL/glew.h>

#include "Core Systems/Logging/Log.h"

#include "Core Systems/Resource Pipeline/Image.h"

namespace Jade {
	class Texture {
	public:
		Texture(int imageFormat, int width, int height, int wrapMode = GL_CLAMP_TO_BORDER, int filter = GL_NEAREST, bool mipmaps = false);
		Texture(const Jade::Image& image);

		void bind() const { glBindTexture(GL_TEXTURE_2D, m_Texture); }
		static void activateUnit(int unit) { glActiveTexture(GL_TEXTURE0 + unit); }

		Image getImage() { return m_Image; }
		unsigned int getTexture() { return m_Texture; } //TODO remove

		void setBorderColour(Colour colour) {
			bind();
			float borderColor[] = { colour.colour.x, colour.colour.y, colour.colour.z, colour.colour.w };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		}

	private:
		Image initBlankImage(int format, int width, int height) {
			int bytesPerPixel{ 0 };
			int channels{ 0 };

			switch (format) {
			default:
			case GL_RGB: bytesPerPixel = 3 * sizeof(float); channels = 3; break;
			case GL_RGBA: bytesPerPixel = 4 * sizeof(float); channels = 4; break;
			case GL_DEPTH_COMPONENT: bytesPerPixel = 1; channels = 1; break;
			}

			std::vector<unsigned char> data;
			data.resize(width * height * bytesPerPixel);

			for (int i = 0; i < data.size(); ++i) {
				data[i] = 0;
			}

			return Image{ data, width, height, bytesPerPixel };
		}

		unsigned int m_Texture;
		Image m_Image;
	};
}