#pragma once

#include <GL/glew.h>

#include "Jade.h"

#include "Core Systems/Resource Pipeline/Image.h"

namespace Jade {
	namespace OpenGL {
		namespace RenderingObjects {
			class Texture {
			public:
				Texture(const Jade::Resources::Image& image);
				Texture(const std::string& path);

				void bind() { glBindTexture(GL_TEXTURE_2D, m_Texture); }
				static void activateUnit(int unit) { glActiveTexture(GL_TEXTURE0 + unit); }

			private:
				unsigned int m_Texture;
				Jade::Resources::Image m_Image;
			};
		}
	}
}